/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.] */

#include <openssl/evp.h>

#include <assert.h>
#include <string.h>

#include <openssl/curve25519.h>
#include <openssl/dsa.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/mem.h>
#include <openssl/nid.h>
#include <openssl/rsa.h>
#include <openssl/thread.h>

#include "internal.h"
#include "../../internal.h"


// Node depends on |EVP_R_NOT_XOF_OR_INVALID_LENGTH|.
//
// TODO(davidben): Fix Node to not touch the error queue itself and remove this.
OPENSSL_DECLARE_ERROR_REASON(EVP, NOT_XOF_OR_INVALID_LENGTH)

// The HPKE module uses the EVP error namespace, but it lives in another
// directory.
OPENSSL_DECLARE_ERROR_REASON(EVP, EMPTY_PSK)

EVP_PKEY *EVP_PKEY_new(void) {
  EVP_PKEY *ret;

  ret = OPENSSL_malloc(sizeof(EVP_PKEY));
  if (ret == NULL) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_MALLOC_FAILURE);
    return NULL;
  }

  OPENSSL_memset(ret, 0, sizeof(EVP_PKEY));
  ret->type = EVP_PKEY_NONE;
  ret->references = 1;

  return ret;
}

static void free_it(EVP_PKEY *pkey) {
  if (pkey->ameth && pkey->ameth->pkey_free) {
    pkey->ameth->pkey_free(pkey);
    pkey->pkey.ptr = NULL;
    pkey->type = EVP_PKEY_NONE;
  }
}

void EVP_PKEY_free(EVP_PKEY *pkey) {
  if (pkey == NULL) {
    return;
  }

  if (!CRYPTO_refcount_dec_and_test_zero(&pkey->references)) {
    return;
  }

  free_it(pkey);
  OPENSSL_free(pkey);
}

int EVP_PKEY_up_ref(EVP_PKEY *pkey) {
  CRYPTO_refcount_inc(&pkey->references);
  return 1;
}

int EVP_PKEY_is_opaque(const EVP_PKEY *pkey) {
  if (pkey->ameth && pkey->ameth->pkey_opaque) {
    return pkey->ameth->pkey_opaque(pkey);
  }
  return 0;
}

int EVP_PKEY_cmp(const EVP_PKEY *a, const EVP_PKEY *b) {
  if (a->type != b->type) {
    return -1;
  }

  if (a->ameth) {
    int ret;
    // Compare parameters if the algorithm has them
    if (a->ameth->param_cmp) {
      ret = a->ameth->param_cmp(a, b);
      if (ret <= 0) {
        return ret;
      }
    }

    if (a->ameth->pub_cmp) {
      return a->ameth->pub_cmp(a, b);
    }
  }

  return -2;
}

int EVP_PKEY_copy_parameters(EVP_PKEY *to, const EVP_PKEY *from) {
  if (to->type == EVP_PKEY_NONE) {
    if (!EVP_PKEY_set_type(to, from->type)) {
      return 0;
    }
  } else if (to->type != from->type) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_DIFFERENT_KEY_TYPES);
    return 0;
  }

  if (EVP_PKEY_missing_parameters(from)) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_MISSING_PARAMETERS);
    return 0;
  }

  // Once set, parameters may not change.
  if (!EVP_PKEY_missing_parameters(to)) {
    if (EVP_PKEY_cmp_parameters(to, from) == 1) {
      return 1;
    }
    OPENSSL_PUT_ERROR(EVP, EVP_R_DIFFERENT_PARAMETERS);
    return 0;
  }

  if (from->ameth && from->ameth->param_copy) {
    return from->ameth->param_copy(to, from);
  }

  // TODO(https://crbug.com/boringssl/536): If the algorithm takes no
  // parameters, copying them should vacuously succeed.
  return 0;
}

int EVP_PKEY_missing_parameters(const EVP_PKEY *pkey) {
  if (pkey->ameth && pkey->ameth->param_missing) {
    return pkey->ameth->param_missing(pkey);
  }
  return 0;
}

int EVP_PKEY_size(const EVP_PKEY *pkey) {
  if (pkey && pkey->ameth && pkey->ameth->pkey_size) {
    return pkey->ameth->pkey_size(pkey);
  }
  return 0;
}

int EVP_PKEY_bits(const EVP_PKEY *pkey) {
  if (pkey && pkey->ameth && pkey->ameth->pkey_bits) {
    return pkey->ameth->pkey_bits(pkey);
  }
  return 0;
}

int EVP_PKEY_id(const EVP_PKEY *pkey) {
  return pkey->type;
}

extern const EVP_PKEY_ASN1_METHOD *const *AWSLC_non_fips_pkey_evp_asn1_methods(void);

// evp_pkey_asn1_find returns the ASN.1 method table for the given |nid|, which
// should be one of the |EVP_PKEY_*| values. It returns NULL if |nid| is
// unknown.
static const EVP_PKEY_ASN1_METHOD *evp_pkey_asn1_find(int nid) {

  const EVP_PKEY_ASN1_METHOD *const *methods = AWSLC_non_fips_pkey_evp_asn1_methods();
  for (size_t i = 0; i < ASN1_EVP_PKEY_METHODS; i++) {
    if (methods[i]->pkey_id == nid) {
      return methods[i];
    }
  }

  return NULL;
}

int EVP_PKEY_type(int nid) {
  const EVP_PKEY_ASN1_METHOD *meth = evp_pkey_asn1_find(nid);
  if (meth == NULL) {
    return NID_undef;
  }
  return meth->pkey_id;
}

int EVP_PKEY_set1_RSA(EVP_PKEY *pkey, RSA *key) {
  if (EVP_PKEY_assign_RSA(pkey, key)) {
    RSA_up_ref(key);
    return 1;
  }
  return 0;
}

int EVP_PKEY_assign_RSA(EVP_PKEY *pkey, RSA *key) {
  return EVP_PKEY_assign(pkey, EVP_PKEY_RSA, key);
}

RSA *EVP_PKEY_get0_RSA(const EVP_PKEY *pkey) {
  if (pkey->type != EVP_PKEY_RSA && pkey->type != EVP_PKEY_RSA_PSS) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_EXPECTING_AN_RSA_KEY);
    return NULL;
  }
  return pkey->pkey.rsa;
}

RSA *EVP_PKEY_get1_RSA(const EVP_PKEY *pkey) {
  RSA *rsa = EVP_PKEY_get0_RSA(pkey);
  if (rsa != NULL) {
    RSA_up_ref(rsa);
  }
  return rsa;
}

int EVP_PKEY_set1_DSA(EVP_PKEY *pkey, DSA *key) {
  if (EVP_PKEY_assign_DSA(pkey, key)) {
    DSA_up_ref(key);
    return 1;
  }
  return 0;
}

int EVP_PKEY_assign_DSA(EVP_PKEY *pkey, DSA *key) {
  return EVP_PKEY_assign(pkey, EVP_PKEY_DSA, key);
}

DSA *EVP_PKEY_get0_DSA(const EVP_PKEY *pkey) {
  if (pkey->type != EVP_PKEY_DSA) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_EXPECTING_A_DSA_KEY);
    return NULL;
  }
  return pkey->pkey.dsa;
}

DSA *EVP_PKEY_get1_DSA(const EVP_PKEY *pkey) {
  DSA *dsa = EVP_PKEY_get0_DSA(pkey);
  if (dsa != NULL) {
    DSA_up_ref(dsa);
  }
  return dsa;
}

int EVP_PKEY_set1_EC_KEY(EVP_PKEY *pkey, EC_KEY *key) {
  if (EVP_PKEY_assign_EC_KEY(pkey, key)) {
    EC_KEY_up_ref(key);
    return 1;
  }
  return 0;
}

int EVP_PKEY_assign_EC_KEY(EVP_PKEY *pkey, EC_KEY *key) {
  return EVP_PKEY_assign(pkey, EVP_PKEY_EC, key);
}

EC_KEY *EVP_PKEY_get0_EC_KEY(const EVP_PKEY *pkey) {
  if (pkey->type != EVP_PKEY_EC) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_EXPECTING_AN_EC_KEY_KEY);
    return NULL;
  }
  return pkey->pkey.ec;
}

EC_KEY *EVP_PKEY_get1_EC_KEY(const EVP_PKEY *pkey) {
  EC_KEY *ec_key = EVP_PKEY_get0_EC_KEY(pkey);
  if (ec_key != NULL) {
    EC_KEY_up_ref(ec_key);
  }
  return ec_key;
}

DH *EVP_PKEY_get0_DH(const EVP_PKEY *pkey) { return NULL; }
DH *EVP_PKEY_get1_DH(const EVP_PKEY *pkey) { return NULL; }

int EVP_PKEY_assign(EVP_PKEY *pkey, int type, void *key) {
  if (!EVP_PKEY_set_type(pkey, type)) {
    return 0;
  }
  pkey->pkey.ptr = key;
  return key != NULL;
}

int EVP_PKEY_set_type(EVP_PKEY *pkey, int type) {
  const EVP_PKEY_ASN1_METHOD *ameth;

  if (pkey && pkey->pkey.ptr) {
    free_it(pkey);
  }

  ameth = evp_pkey_asn1_find(type);
  if (ameth == NULL) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_UNSUPPORTED_ALGORITHM);
    ERR_add_error_dataf("algorithm %d", type);
    return 0;
  }

  if (pkey) {
    pkey->ameth = ameth;
    pkey->type = pkey->ameth->pkey_id;
  }

  return 1;
}

EVP_PKEY *EVP_PKEY_new_raw_private_key(int type, ENGINE *unused,
                                       const uint8_t *in, size_t len) {
  EVP_PKEY *ret = EVP_PKEY_new();
  if (ret == NULL ||
      !EVP_PKEY_set_type(ret, type)) {
    goto err;
  }

  if (ret->ameth->set_priv_raw == NULL) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
    goto err;
  }

  if (!ret->ameth->set_priv_raw(ret, in, len, NULL, 0)) {
    goto err;
  }

  return ret;

err:
  EVP_PKEY_free(ret);
  return NULL;
}

EVP_PKEY *EVP_PKEY_new_raw_public_key(int type, ENGINE *unused,
                                      const uint8_t *in, size_t len) {
  EVP_PKEY *ret = EVP_PKEY_new();
  if (ret == NULL ||
      !EVP_PKEY_set_type(ret, type)) {
    goto err;
  }

  if (ret->ameth->set_pub_raw == NULL) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
    goto err;
  }

  if (!ret->ameth->set_pub_raw(ret, in, len)) {
    goto err;
  }

  return ret;

err:
  EVP_PKEY_free(ret);
  return NULL;
}

int EVP_PKEY_get_raw_private_key(const EVP_PKEY *pkey, uint8_t *out,
                                 size_t *out_len) {
  if (pkey->ameth->get_priv_raw == NULL) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
    return 0;
  }

  return pkey->ameth->get_priv_raw(pkey, out, out_len);
}

int EVP_PKEY_get_raw_public_key(const EVP_PKEY *pkey, uint8_t *out,
                                size_t *out_len) {
  if (pkey->ameth->get_pub_raw == NULL) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
    return 0;
  }

  return pkey->ameth->get_pub_raw(pkey, out, out_len);
}

int EVP_PKEY_cmp_parameters(const EVP_PKEY *a, const EVP_PKEY *b) {
  if (a->type != b->type) {
    return -1;
  }
  if (a->ameth && a->ameth->param_cmp) {
    return a->ameth->param_cmp(a, b);
  }
  // TODO(https://crbug.com/boringssl/536): If the algorithm doesn't use
  // parameters, they should compare as vacuously equal.
  return -2;
}

int EVP_PKEY_CTX_set_signature_md(EVP_PKEY_CTX *ctx, const EVP_MD *md) {
  return EVP_PKEY_CTX_ctrl(ctx, -1, EVP_PKEY_OP_TYPE_SIG, EVP_PKEY_CTRL_MD, 0,
                           (void *)md);
}

int EVP_PKEY_CTX_get_signature_md(EVP_PKEY_CTX *ctx, const EVP_MD **out_md) {
  return EVP_PKEY_CTX_ctrl(ctx, -1, EVP_PKEY_OP_TYPE_SIG, EVP_PKEY_CTRL_GET_MD,
                           0, (void *)out_md);
}

void *EVP_PKEY_get0(const EVP_PKEY *pkey) {
  // Node references, but never calls this function, so for now we return NULL.
  // If other projects require complete support, call |EVP_PKEY_get0_RSA|, etc.,
  // rather than reading |pkey->pkey.ptr| directly. This avoids problems if our
  // internal representation does not match the type the caller expects from
  // OpenSSL.
  return NULL;
}

void OpenSSL_add_all_algorithms(void) {}

void OPENSSL_add_all_algorithms_conf(void) {}

void OpenSSL_add_all_ciphers(void) {}

void OpenSSL_add_all_digests(void) {}

void EVP_cleanup(void) {}

int EVP_PKEY_base_id(const EVP_PKEY *pkey) {
  // OpenSSL has two notions of key type because it supports multiple OIDs for
  // the same algorithm: NID_rsa vs NID_rsaEncryption and five distinct spelling
  // of DSA. We do not support these, so the base ID is simply the ID.
  return EVP_PKEY_id(pkey);
}

static int evp_pkey_tls_encodedpoint_ec_curve_supported(const EC_KEY *ec_key) {

  int ret = 0;
  int curve_nid = 0;
  const EC_GROUP *ec_key_group = NULL;

  if (NULL == ec_key) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_PASSED_NULL_PARAMETER);
    goto err;
  }

  ec_key_group = EC_KEY_get0_group(ec_key);
  if (NULL == ec_key_group) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_MISSING_PARAMETERS);
    goto err;
  }

  curve_nid = EC_GROUP_get_curve_name(ec_key_group);
  if ((NID_secp224r1 != curve_nid) &&
      (NID_X9_62_prime256v1 != curve_nid) &&
      (NID_secp384r1 != curve_nid) &&
      (NID_secp521r1 != curve_nid)) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
    goto err;
  }

  ret = 1;

err:
  return ret;
}

static int evp_pkey_set1_tls_encodedpoint_ec_key(EVP_PKEY *pkey,
                                                  const uint8_t *in,
                                                  size_t len) {
  int ret = 0;
  EC_KEY *ec_key = NULL;
  const EC_GROUP *ec_key_group = NULL;
  EC_POINT *ec_point = NULL;

  if ((NULL == pkey) || (NULL == in)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_PASSED_NULL_PARAMETER);
    goto err;
  }

  if (1 > len) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_INVALID_PARAMETERS);
    goto err;
  }

  if (EVP_PKEY_EC != pkey->type) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
    goto err;
  }

  // This function is TLS-specific. Only support TLS EC point representation,
  // which must be uncompressed
  // (https://tools.ietf.org/html/rfc8422#section-5.4.1)
  // TLS wire-encoding format for supported NIST curves are:
  // compression || x-coordinate || y-coordinate
  // where:
  // compression = 0x04 if uncompressed
  // compression = 0x02/0x03 if compressed (depending on y-coordinate parity)
  if (POINT_CONVERSION_UNCOMPRESSED != in[0]) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  ec_key = EVP_PKEY_get0_EC_KEY(pkey);
  if (NULL == ec_key) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_NO_KEY_SET);
    goto err;
  }

  if (0 == evp_pkey_tls_encodedpoint_ec_curve_supported(ec_key)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  ec_key_group = EC_KEY_get0_group(ec_key);
  if (NULL == ec_key_group) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_MISSING_PARAMETERS);
    goto err;
  }

  ec_point = EC_POINT_new(ec_key_group);
  if (NULL == ec_point) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  if (0 == EC_POINT_oct2point(ec_key_group, ec_point, in, len, NULL)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  if (0 == EC_KEY_set_public_key(ec_key, (const EC_POINT *) ec_point)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  ret = 1;

err:
  EC_POINT_free(ec_point);
  return ret;
}

static int evp_pkey_set1_tls_encodedpoint_x25519(EVP_PKEY *pkey,
                                                    const uint8_t *in,
                                                    size_t len) {
  int ret = 0;

  if ((NULL == pkey) || (NULL == in)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_PASSED_NULL_PARAMETER);
    goto err;
  }

  if (EVP_PKEY_X25519 != pkey->type) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
    goto err;
  }

  if (1 > len) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_INVALID_PARAMETERS);
    goto err;
  }

  if ((NULL == pkey->ameth) || (NULL == pkey->ameth->set_pub_raw)) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
    goto err;
  }

  if (0 == pkey->ameth->set_pub_raw(pkey, in, len)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  ret = 1;

err:
  return ret;
}

int EVP_PKEY_set1_tls_encodedpoint(EVP_PKEY *pkey, const uint8_t *in,
                                    size_t len) {

  if (NULL == pkey) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_PASSED_NULL_PARAMETER);
    goto err;
  }

  switch (pkey->type) {
    case EVP_PKEY_X25519:
      return evp_pkey_set1_tls_encodedpoint_x25519(pkey, in, len);
    case EVP_PKEY_EC:
      return evp_pkey_set1_tls_encodedpoint_ec_key(pkey, in, len);
    default:
      OPENSSL_PUT_ERROR(EVP, EVP_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
      goto err;
  }

err:
  return 0;
}

static size_t evp_pkey_get1_tls_encodedpoint_ec_key(const EVP_PKEY *pkey,
                                                      uint8_t **out_ptr) {

  size_t ret = 0;
  const EC_KEY *ec_key = NULL;

  if ((NULL == pkey) || (NULL == out_ptr)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_PASSED_NULL_PARAMETER);
    goto err;
  }

  if (EVP_PKEY_EC != pkey->type) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
    goto err;
  }

  ec_key = EVP_PKEY_get0_EC_KEY(pkey);
  if (NULL == ec_key) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_NO_KEY_SET);
    goto err;
  }

  if (0 == evp_pkey_tls_encodedpoint_ec_curve_supported(ec_key)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  // This function is TLS-specific. Only support TLS EC point representation,
  // which must be uncompressed
  // (https://tools.ietf.org/html/rfc8422#section-5.4.1)
  if (POINT_CONVERSION_UNCOMPRESSED != EC_KEY_get_conv_form(ec_key)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  // Returns the length of |*out_ptr|
  ret = EC_KEY_key2buf(ec_key, POINT_CONVERSION_UNCOMPRESSED, out_ptr, NULL);
  if (0 == ret) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

err:
  return ret;
}

static size_t evp_pkey_get1_tls_encodedpoint_x25519(const EVP_PKEY *pkey,
                                                      uint8_t **out_ptr) {

  size_t ret = 0;
  size_t out_len = 0;

  if ((NULL == pkey) || (NULL == out_ptr)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_PASSED_NULL_PARAMETER);
    return 0;
  }

  if (EVP_PKEY_X25519 != pkey->type) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
    return 0;
  }

  if ((NULL == pkey->ameth) || (NULL == pkey->ameth->get_pub_raw)) {
    OPENSSL_PUT_ERROR(EVP, EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
    return 0;
  }

  out_len = X25519_SHARED_KEY_LEN;
  *out_ptr = OPENSSL_malloc(X25519_SHARED_KEY_LEN);
  if (NULL == *out_ptr) {
    OPENSSL_PUT_ERROR(CRYPTO, ERR_R_MALLOC_FAILURE);
    return 0;
  }

  if (0 == pkey->ameth->get_pub_raw(pkey, *out_ptr, &out_len)) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  if (X25519_SHARED_KEY_LEN != out_len) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_EVP_LIB);
    goto err;
  }

  ret = X25519_SHARED_KEY_LEN;

err:
  if (0 == ret) {
    OPENSSL_free(*out_ptr);
    *out_ptr = NULL;
  }
  return ret;
}

size_t EVP_PKEY_get1_tls_encodedpoint(const EVP_PKEY *pkey, uint8_t **out_ptr) {

  if (NULL == pkey) {
    OPENSSL_PUT_ERROR(EVP, ERR_R_PASSED_NULL_PARAMETER);
    goto err;
  }

  switch (pkey->type) {
    case EVP_PKEY_X25519:
      return evp_pkey_get1_tls_encodedpoint_x25519(pkey, out_ptr);
    case EVP_PKEY_EC:
      return evp_pkey_get1_tls_encodedpoint_ec_key(pkey, out_ptr);
    default:
      OPENSSL_PUT_ERROR(EVP, EVP_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
      goto err;
    }

err:
  return 0;
}
