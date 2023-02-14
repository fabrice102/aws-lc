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

#include <string.h>

#include <openssl/asn1.h>
#include <openssl/digest.h>
#include <openssl/err.h>
#include <openssl/mem.h>
#include <openssl/obj.h>
#include <openssl/stack.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

#include "../internal.h"
#include "../x509v3/internal.h"
#include "internal.h"


int X509_issuer_name_cmp(const X509 *a, const X509 *b) {
  return (X509_NAME_cmp(a->cert_info->issuer, b->cert_info->issuer));
}

int X509_subject_name_cmp(const X509 *a, const X509 *b) {
  return (X509_NAME_cmp(a->cert_info->subject, b->cert_info->subject));
}

int X509_CRL_cmp(const X509_CRL *a, const X509_CRL *b) {
  return (X509_NAME_cmp(a->crl->issuer, b->crl->issuer));
}

int X509_CRL_match(const X509_CRL *a, const X509_CRL *b) {
  return OPENSSL_memcmp(a->crl_hash, b->crl_hash, SHA256_DIGEST_LENGTH);
}

X509_NAME *X509_get_issuer_name(const X509 *a) {
  return a->cert_info->issuer;
}

unsigned long X509_issuer_name_hash(X509 *x) {
  return (X509_NAME_hash(x->cert_info->issuer));
}

unsigned long X509_issuer_name_hash_old(X509 *x) {
  return (X509_NAME_hash_old(x->cert_info->issuer));
}

X509_NAME *X509_get_subject_name(const X509 *a) {
  return a->cert_info->subject;
}

ASN1_INTEGER *X509_get_serialNumber(X509 *a) {
  return a->cert_info->serialNumber;
}

const ASN1_INTEGER *X509_get0_serialNumber(const X509 *x509) {
  return x509->cert_info->serialNumber;
}

unsigned long X509_subject_name_hash(X509 *x) {
  return (X509_NAME_hash(x->cert_info->subject));
}

unsigned long X509_subject_name_hash_old(X509 *x) {
  return (X509_NAME_hash_old(x->cert_info->subject));
}

// Compare two certificates: they must be identical for this to work. NB:
// Although "cmp" operations are generally prototyped to take "const"
// arguments (eg. for use in STACKs), the way X509 handling is - these
// operations may involve ensuring the hashes are up-to-date and ensuring
// certain cert information is cached. So this is the point where the
// "depth-first" constification tree has to halt with an evil cast.
int X509_cmp(const X509 *a, const X509 *b) {
  // Fill in the |cert_hash| fields.
  //
  // TODO(davidben): This may fail, in which case the the hash will be all
  // zeros. This produces a consistent comparison (failures are sticky), but
  // not a good one. OpenSSL now returns -2, but this is not a consistent
  // comparison and may cause misbehaving sorts by transitivity. For now, we
  // retain the old OpenSSL behavior, which was to ignore the error. See
  // https://crbug.com/boringssl/355.
  x509v3_cache_extensions((X509 *)a);
  x509v3_cache_extensions((X509 *)b);

  return OPENSSL_memcmp(a->cert_hash, b->cert_hash, SHA256_DIGEST_LENGTH);
}

int X509_NAME_cmp(const X509_NAME *a, const X509_NAME *b) {
  int ret;

  // Ensure canonical encoding is present and up to date

  if (!a->canon_enc || a->modified) {
    ret = i2d_X509_NAME((X509_NAME *)a, NULL);
    if (ret < 0) {
      return -2;
    }
  }

  if (!b->canon_enc || b->modified) {
    ret = i2d_X509_NAME((X509_NAME *)b, NULL);
    if (ret < 0) {
      return -2;
    }
  }

  ret = a->canon_enclen - b->canon_enclen;

  if (ret) {
    return ret;
  }

  return OPENSSL_memcmp(a->canon_enc, b->canon_enc, a->canon_enclen);
}

unsigned long X509_NAME_hash(X509_NAME *x) {
  unsigned long ret = 0;
  unsigned char md[SHA_DIGEST_LENGTH];

  // Make sure X509_NAME structure contains valid cached encoding
  i2d_X509_NAME(x, NULL);
  if (!EVP_Digest(x->canon_enc, x->canon_enclen, md, NULL, EVP_sha1(), NULL)) {
    return 0;
  }

  ret = (((unsigned long)md[0]) | ((unsigned long)md[1] << 8L) |
         ((unsigned long)md[2] << 16L) | ((unsigned long)md[3] << 24L)) &
        0xffffffffL;
  return ret;
}

// I now DER encode the name and hash it.  Since I cache the DER encoding,
// this is reasonably efficient.

unsigned long X509_NAME_hash_old(X509_NAME *x) {
  EVP_MD_CTX md_ctx;
  unsigned long ret = 0;
  unsigned char md[16];

  // Make sure X509_NAME structure contains valid cached encoding
  i2d_X509_NAME(x, NULL);
  EVP_MD_CTX_init(&md_ctx);
  // EVP_MD_CTX_set_flags(&md_ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
  if (EVP_DigestInit_ex(&md_ctx, EVP_md5(), NULL) &&
      EVP_DigestUpdate(&md_ctx, x->bytes->data, x->bytes->length) &&
      EVP_DigestFinal_ex(&md_ctx, md, NULL)) {
    ret = (((unsigned long)md[0]) | ((unsigned long)md[1] << 8L) |
           ((unsigned long)md[2] << 16L) | ((unsigned long)md[3] << 24L)) &
          0xffffffffL;
  }
  EVP_MD_CTX_cleanup(&md_ctx);

  return ret;
}

X509 *X509_find_by_issuer_and_serial(const STACK_OF(X509) *sk, X509_NAME *name,
                                     const ASN1_INTEGER *serial) {
  if (serial->type != V_ASN1_INTEGER && serial->type != V_ASN1_NEG_INTEGER) {
    return NULL;
  }

  for (size_t i = 0; i < sk_X509_num(sk); i++) {
    X509 *x509 = sk_X509_value(sk, i);
    if (ASN1_INTEGER_cmp(X509_get0_serialNumber(x509), serial) == 0 &&
        X509_NAME_cmp(X509_get_issuer_name(x509), name) == 0) {
      return x509;
    }
  }
  return NULL;
}

X509 *X509_find_by_subject(const STACK_OF(X509) *sk, X509_NAME *name) {
  for (size_t i = 0; i < sk_X509_num(sk); i++) {
    X509 *x509 = sk_X509_value(sk, i);
    if (X509_NAME_cmp(X509_get_subject_name(x509), name) == 0) {
      return x509;
    }
  }
  return NULL;
}

EVP_PKEY *X509_get_pubkey(X509 *x) {
  if ((x == NULL) || (x->cert_info == NULL)) {
    return NULL;
  }
  return (X509_PUBKEY_get(x->cert_info->key));
}

ASN1_BIT_STRING *X509_get0_pubkey_bitstr(const X509 *x) {
  if (!x) {
    return NULL;
  }
  return x->cert_info->key->public_key;
}

int X509_check_private_key(X509 *x, const EVP_PKEY *k) {
  EVP_PKEY *xk;
  int ret;

  xk = X509_get_pubkey(x);

  if (xk) {
    ret = EVP_PKEY_cmp(xk, k);
  } else {
    ret = -2;
  }

  switch (ret) {
    case 1:
      break;
    case 0:
      OPENSSL_PUT_ERROR(X509, X509_R_KEY_VALUES_MISMATCH);
      break;
    case -1:
      OPENSSL_PUT_ERROR(X509, X509_R_KEY_TYPE_MISMATCH);
      break;
    case -2:
      OPENSSL_PUT_ERROR(X509, X509_R_UNKNOWN_KEY_TYPE);
  }
  if (xk) {
    EVP_PKEY_free(xk);
  }
  if (ret > 0) {
    return 1;
  }
  return 0;
}

// Not strictly speaking an "up_ref" as a STACK doesn't have a reference
// count but it has the same effect by duping the STACK and upping the ref of
// each X509 structure.
STACK_OF(X509) *X509_chain_up_ref(STACK_OF(X509) *chain) {
  STACK_OF(X509) *ret;
  size_t i;
  ret = sk_X509_dup(chain);
  for (i = 0; i < sk_X509_num(ret); i++) {
    X509_up_ref(sk_X509_value(ret, i));
  }
  return ret;
}
