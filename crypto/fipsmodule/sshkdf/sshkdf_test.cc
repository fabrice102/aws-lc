// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>

#include <openssl/crypto.h>
#include <openssl/digest.h>
#include <openssl/sshkdf.h>

#include "../../internal.h"
#include "../../test/test_util.h"

// SSHKDF test vectors from NIST CAVS 14.1 test vectors
// https://csrc.nist.gov/Projects/Cryptographic-Algorithm-Validation-Program/Component-Testing#KDF135

static void test_sshkdf(const EVP_MD *evp_md, const uint8_t *key, size_t key_len,
    const uint8_t *xcghash, size_t xcghash_len,
    const uint8_t *session_id, size_t session_id_len,
    char type,
    uint8_t *out, size_t out_len,
    const uint8_t *expected_output) {
    // Initial IVs
    ASSERT_TRUE(SSHKDF(evp_md, key, key_len, xcghash, xcghash_len,
        session_id, session_id_len, type,
        out, out_len));
    EXPECT_EQ(Bytes(expected_output, sizeof(out_len)),
        Bytes(out, sizeof(out_len)));
}

TEST(SSHKDFTest, SSHKDF_INPUT_INSANITY) {
    uint8_t not_empty[] = {'t', 'e', 's', 't'};
    size_t not_empty_len = sizeof(not_empty);
    uint8_t output[] = {0};
    size_t output_len = sizeof(output);
    const EVP_MD *md = EVP_sha256();  // Not actually used.

    ASSERT_FALSE(SSHKDF(nullptr, not_empty, not_empty_len,
                        not_empty, not_empty_len, not_empty, not_empty_len,
                        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
                        output, output_len));

    ASSERT_FALSE(SSHKDF(md, nullptr, not_empty_len,
                        not_empty, not_empty_len, not_empty, not_empty_len,
                        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
                        output, output_len));
    ASSERT_FALSE(SSHKDF(md, not_empty, 0,
                        not_empty, not_empty_len, not_empty, not_empty_len,
                        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
                        output, output_len));

    ASSERT_FALSE(SSHKDF(md, not_empty, not_empty_len,
                        nullptr, not_empty_len, not_empty, not_empty_len,
                        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
                        output, output_len));
    ASSERT_FALSE(SSHKDF(md, not_empty, not_empty_len,
                        not_empty, 0, not_empty, not_empty_len,
                        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
                        output, output_len));

    ASSERT_FALSE(SSHKDF(md, not_empty, not_empty_len,
                        not_empty, not_empty_len, nullptr, not_empty_len,
                        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
                        output, output_len));
    ASSERT_FALSE(SSHKDF(md, not_empty, not_empty_len,
                        not_empty, not_empty_len, not_empty, 0,
                        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
                        output, output_len));

    ASSERT_FALSE(SSHKDF(md, not_empty, not_empty_len,
                        not_empty, not_empty_len, not_empty, not_empty_len,
                        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV - 1,
                        output, output_len));
    ASSERT_FALSE(SSHKDF(md, not_empty, not_empty_len,
                        not_empty, not_empty_len, not_empty, not_empty_len,
                        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_SRV_TO_CLI + 1,
                        output, output_len));
}

TEST(SSHKDFTest, SSHKDF_SHA1) {
    const uint8_t key[] = {
        0x00, 0x00, 0x00, 0x80, 0x55, 0xba, 0xe9, 0x31, 0xc0, 0x7f, 0xd8, 0x24,
        0xbf, 0x10, 0xad, 0xd1, 0x90, 0x2b, 0x6f, 0xbc, 0x7c, 0x66, 0x53, 0x47,
        0x38, 0x34, 0x98, 0xa6, 0x86, 0x92, 0x9f, 0xf5, 0xa2, 0x5f, 0x8e, 0x40,
        0xcb, 0x66, 0x45, 0xea, 0x81, 0x4f, 0xb1, 0xa5, 0xe0, 0xa1, 0x1f, 0x85,
        0x2f, 0x86, 0x25, 0x56, 0x41, 0xe5, 0xed, 0x98, 0x6e, 0x83, 0xa7, 0x8b,
        0xc8, 0x26, 0x94, 0x80, 0xea, 0xc0, 0xb0, 0xdf, 0xd7, 0x70, 0xca, 0xb9,
        0x2e, 0x7a, 0x28, 0xdd, 0x87, 0xff, 0x45, 0x24, 0x66, 0xd6, 0xae, 0x86,
        0x7c, 0xea, 0xd6, 0x3b, 0x36, 0x6b, 0x1c, 0x28, 0x6e, 0x6c, 0x48, 0x11,
        0xa9, 0xf1, 0x4c, 0x27, 0xae, 0xa1, 0x4c, 0x51, 0x71, 0xd4, 0x9b, 0x78,
        0xc0, 0x6e, 0x37, 0x35, 0xd3, 0x6e, 0x6a, 0x3b, 0xe3, 0x21, 0xdd, 0x5f,
        0xc8, 0x23, 0x08, 0xf3, 0x4e, 0xe1, 0xcb, 0x17, 0xfb, 0xa9, 0x4a, 0x59
    };
    const uint8_t xcghash[] = {
        0xa4, 0xeb, 0xd4, 0x59, 0x34, 0xf5, 0x67, 0x92, 0xb5, 0x11, 0x2d, 0xcd,
        0x75, 0xa1, 0x07, 0x5f, 0xdc, 0x88, 0x92, 0x45
    };
    const uint8_t session_id[] = {
        0xa4, 0xeb, 0xd4, 0x59, 0x34, 0xf5, 0x67, 0x92, 0xb5, 0x11, 0x2d, 0xcd,
        0x75, 0xa1, 0x07, 0x5f, 0xdc, 0x88, 0x92, 0x45
    };

    const uint8_t initial_iv_c2s[] = {
        0xe2, 0xf6, 0x27, 0xc0, 0xb4, 0x3f, 0x1a, 0xc1
    };
    const uint8_t initial_iv_s2c[] = {
        0x58, 0x47, 0x14, 0x45, 0xf3, 0x42, 0xb1, 0x81
    };

    const uint8_t encryption_key_c2s[] = {
        0x1c, 0xa9, 0xd3, 0x10, 0xf8, 0x6d, 0x51, 0xf6, 0xcb, 0x8e, 0x70, 0x07,
        0xcb, 0x2b, 0x22, 0x0d, 0x55, 0xc5, 0x28, 0x1c, 0xe6, 0x80, 0xb5, 0x33
    };
    const uint8_t encryption_key_s2c[] = {
        0x2c, 0x60, 0xdf, 0x86, 0x03, 0xd3, 0x4c, 0xc1, 0xdb, 0xb0, 0x3c, 0x11,
        0xf7, 0x25, 0xa4, 0x4b, 0x44, 0x00, 0x88, 0x51, 0xc7, 0x3d, 0x68, 0x44
    };

    const uint8_t integrity_key_c2s[] = {
        0x47, 0x2e, 0xb8, 0xa2, 0x61, 0x66, 0xae, 0x6a, 0xa8, 0xe0, 0x68, 0x68,
        0xe4, 0x5c, 0x3b, 0x26, 0xe6, 0xee, 0xed, 0x06
    };
    const uint8_t integrity_key_s2c[] = {
        0xe3, 0xe2, 0xfd, 0xb9, 0xd7, 0xbc, 0x21, 0x16, 0x5a, 0x3d, 0xbe, 0x47,
        0xe1, 0xec, 0xeb, 0x77, 0x64, 0x39, 0x0b, 0xab
    };

    uint8_t output[sizeof(encryption_key_c2s)] = {0};  // longest output

    // Initial IVs
    test_sshkdf(EVP_sha1(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
        output, sizeof(initial_iv_c2s),
        initial_iv_c2s);

    test_sshkdf(EVP_sha1(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_SRV_TO_CLI,
        output, sizeof(initial_iv_s2c),
        initial_iv_s2c);

    // Encryption keys
    test_sshkdf(EVP_sha1(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_CLI_TO_SRV,
        output, sizeof(encryption_key_c2s),
        encryption_key_c2s);

    test_sshkdf(EVP_sha1(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_SRV_TO_CLI,
        output, sizeof(encryption_key_s2c),
        encryption_key_s2c);

    // Integrity keys
    test_sshkdf(EVP_sha1(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_CLI_TO_SRV,
        output, sizeof(integrity_key_c2s),
        integrity_key_c2s);

    test_sshkdf(EVP_sha1(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_SRV_TO_CLI,
        output, sizeof(integrity_key_s2c),
        integrity_key_s2c);
}

TEST(SSHKDFTest, SSHKDF_SHA224) {
    const uint8_t key[] = {
        0x00, 0x00, 0x00, 0x81, 0x00, 0x8d, 0xe6, 0x0d, 0xf0, 0x19, 0xc2, 0x39,
        0x66, 0xd2, 0x15, 0xd9, 0xb8, 0x49, 0x0a, 0xc4, 0x93, 0xdf, 0xae, 0x59,
        0xb9, 0x9d, 0xbe, 0xfd, 0xad, 0x81, 0xd2, 0xc9, 0xe7, 0x61, 0x20, 0x5c,
        0x93, 0xa6, 0x96, 0xdb, 0xd9, 0xe5, 0x38, 0xcc, 0x57, 0xcd, 0x3e, 0x24,
        0xc2, 0x79, 0x8d, 0x2c, 0x56, 0x56, 0x1d, 0x68, 0x03, 0xe8, 0xee, 0x24,
        0xe1, 0x12, 0xba, 0xbe, 0xf8, 0x4a, 0xd5, 0xa2, 0xc5, 0x71, 0xc5, 0x72,
        0x33, 0x9f, 0x2b, 0x38, 0xf1, 0x34, 0x51, 0x64, 0x31, 0x4f, 0x8f, 0x47,
        0x14, 0x04, 0x7f, 0x0c, 0x66, 0x65, 0x0f, 0x10, 0x05, 0x10, 0x44, 0xf8,
        0xdc, 0xd2, 0x56, 0xbf, 0xe8, 0x17, 0x13, 0x02, 0xa8, 0x1c, 0xe1, 0x3f,
        0x47, 0xf7, 0x37, 0x5d, 0xb8, 0x0a, 0x6b, 0xbf, 0x8c, 0xe7, 0xd8, 0xf9,
        0x6e, 0x03, 0xfc, 0x62, 0x75, 0xfd, 0x5d, 0xac, 0xfb, 0xdd, 0x16, 0x67,
        0x92
    };
    const uint8_t xcghash[] = {
        0xe6, 0x9f, 0xbb, 0xee, 0x90, 0xf0, 0xcb, 0x7c, 0x57, 0x99, 0x6c, 0x6f,
        0x3f, 0x9e, 0xc4, 0xc7, 0xde, 0x9f, 0x0c, 0x43, 0xb7, 0xc9, 0x93, 0xec,
        0x3e, 0xc1, 0xd4, 0xca
    };
    const uint8_t session_id[] = {
        0xe6, 0x9f, 0xbb, 0xee, 0x90, 0xf0, 0xcb, 0x7c, 0x57, 0x99, 0x6c, 0x6f,
        0x3f, 0x9e, 0xc4, 0xc7, 0xde, 0x9f, 0x0c, 0x43, 0xb7, 0xc9, 0x93, 0xec,
        0x3e, 0xc1, 0xd4, 0xca
    };

    const uint8_t initial_iv_c2s[] = {
        0x9f, 0xff, 0x6c, 0x6a, 0x6d, 0x1f, 0x5c, 0x31
    };
    const uint8_t initial_iv_s2c[] = {
        0x8e, 0x0a, 0xe7, 0x8c, 0x64, 0xd2, 0xfe, 0x2a
    };

    const uint8_t encryption_key_c2s[] = {
        0x90, 0x44, 0xf9, 0x63, 0xff, 0xb5, 0x6b, 0x94, 0x55, 0x6a, 0x38, 0xaa,
        0xc5, 0x39, 0x8a, 0x70, 0x72, 0xff, 0xba, 0x60, 0x25, 0x85, 0x00, 0xbe
    };
    const uint8_t encryption_key_s2c[] = {
        0xa8, 0x61, 0xa3, 0x17, 0xea, 0x42, 0xb0, 0x50, 0x90, 0x1a, 0xff, 0x36,
        0x7b, 0x5a, 0x1d, 0x0a, 0xbd, 0x5c, 0x49, 0x7c, 0x77, 0x31, 0x1b, 0xa2
    };

    const uint8_t integrity_key_c2s[] = {
        0x43, 0x22, 0x5d, 0x64, 0xb6, 0xda, 0x6f, 0x07, 0x09, 0x25, 0xad, 0x1c,
        0x8b, 0x7a, 0xc8, 0x88, 0x93, 0xf9, 0xa7, 0xcb, 0xa0, 0xdf, 0xc5, 0x5d,
        0xde, 0xa4, 0x2e, 0xec
    };
    const uint8_t integrity_key_s2c[] = {
        0xeb, 0x31, 0xdb, 0x29, 0xbb, 0xaf, 0xca, 0x27, 0x73, 0xf8, 0x15, 0xfa,
        0x47, 0x8d, 0x92, 0x79, 0x43, 0x28, 0x85, 0x88, 0xe3, 0x71, 0xae, 0x9b,
        0xa0, 0x41, 0x4d, 0x98
    };

    uint8_t output[sizeof(integrity_key_c2s)] = {0};  // longest output

    // Initial IVs
    test_sshkdf(EVP_sha224(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
        output, sizeof(initial_iv_c2s),
        initial_iv_c2s);

    test_sshkdf(EVP_sha224(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_SRV_TO_CLI,
        output, sizeof(initial_iv_s2c),
        initial_iv_s2c);

    // Encryption keys
    test_sshkdf(EVP_sha224(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_CLI_TO_SRV,
        output, sizeof(encryption_key_c2s),
        encryption_key_c2s);

    test_sshkdf(EVP_sha224(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_SRV_TO_CLI,
        output, sizeof(encryption_key_s2c),
        encryption_key_s2c);

    // Integrity keys
    test_sshkdf(EVP_sha224(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_CLI_TO_SRV,
        output, sizeof(integrity_key_c2s),
        integrity_key_c2s);

    test_sshkdf(EVP_sha224(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_SRV_TO_CLI,
        output, sizeof(integrity_key_s2c),
        integrity_key_s2c);
}

TEST(SSHKDFTest, SSHKDF_SHA256) {
    const uint8_t key[] = {
        0x00, 0x00, 0x00, 0x81, 0x00, 0x87, 0x5c, 0x55, 0x1c, 0xef, 0x52, 0x6a,
        0x4a, 0x8b, 0xe1, 0xa7, 0xdf, 0x27, 0xe9, 0xed, 0x35, 0x4b, 0xac, 0x9a,
        0xfb, 0x71, 0xf5, 0x3d, 0xba, 0xe9, 0x05, 0x67, 0x9d, 0x14, 0xf9, 0xfa,
        0xf2, 0x46, 0x9c, 0x53, 0x45, 0x7c, 0xf8, 0x0a, 0x36, 0x6b, 0xe2, 0x78,
        0x96, 0x5b, 0xa6, 0x25, 0x52, 0x76, 0xca, 0x2d, 0x9f, 0x4a, 0x97, 0xd2,
        0x71, 0xf7, 0x1e, 0x50, 0xd8, 0xa9, 0xec, 0x46, 0x25, 0x3a, 0x6a, 0x90,
        0x6a, 0xc2, 0xc5, 0xe4, 0xf4, 0x8b, 0x27, 0xa6, 0x3c, 0xe0, 0x8d, 0x80,
        0x39, 0x0a, 0x49, 0x2a, 0xa4, 0x3b, 0xad, 0x9d, 0x88, 0x2c, 0xca, 0xc2,
        0x3d, 0xac, 0x88, 0xbc, 0xad, 0xa4, 0xb4, 0xd4, 0x26, 0xa3, 0x62, 0x08,
        0x3d, 0xab, 0x65, 0x69, 0xc5, 0x4c, 0x22, 0x4d, 0xd2, 0xd8, 0x76, 0x43,
        0xaa, 0x22, 0x76, 0x93, 0xe1, 0x41, 0xad, 0x16, 0x30, 0xce, 0x13, 0x14,
        0x4e
    };
    const uint8_t xcghash[] = {
        0x0e, 0x68, 0x3f, 0xc8, 0xa9, 0xed, 0x7c, 0x2f, 0xf0, 0x2d, 0xef, 0x23,
        0xb2, 0x74, 0x5e, 0xbc, 0x99, 0xb2, 0x67, 0xda, 0xa8, 0x6a, 0x4a, 0xa7,
        0x69, 0x72, 0x39, 0x08, 0x82, 0x53, 0xf6, 0x42
    };
    const uint8_t session_id[] = {
        0x0e, 0x68, 0x3f, 0xc8, 0xa9, 0xed, 0x7c, 0x2f, 0xf0, 0x2d, 0xef, 0x23,
        0xb2, 0x74, 0x5e, 0xbc, 0x99, 0xb2, 0x67, 0xda, 0xa8, 0x6a, 0x4a, 0xa7,
        0x69, 0x72, 0x39, 0x08, 0x82, 0x53, 0xf6, 0x42
    };

    const uint8_t initial_iv_c2s[] = {
        0x41, 0xff, 0x2e, 0xad, 0x16, 0x83, 0xf1, 0xe6
    };
    const uint8_t initial_iv_s2c[] = {
        0xe6, 0x19, 0xec, 0xfd, 0x9e, 0xdb, 0x50, 0xcd
    };

    const uint8_t encryption_key_c2s[] = {
        0x4a, 0x63, 0x14, 0xd2, 0xf7, 0x51, 0x1b, 0xf8, 0x8f, 0xad, 0x39, 0xfb,
        0x68, 0x92, 0xf3, 0xf2, 0x18, 0xca, 0xfd, 0x53, 0x0e, 0x72, 0xfe, 0x43
    };
    const uint8_t encryption_key_s2c[] = {
        0x08, 0x4c, 0x15, 0xfb, 0x7f, 0x99, 0xc6, 0x5f, 0xf1, 0x34, 0xee, 0xb4,
        0x07, 0xce, 0xe5, 0xd5, 0x40, 0xc3, 0x41, 0xde, 0xa4, 0x5a, 0x42, 0xa5
    };

    const uint8_t integrity_key_c2s[] = {
        0x41, 0xec, 0x5a, 0x94, 0xfe, 0xcc, 0xe7, 0x70, 0x7e, 0xa1, 0x56, 0xa6,
        0xad, 0x29, 0x23, 0x9a, 0x89, 0x16, 0x21, 0xad, 0xac, 0xbe, 0xdb, 0x8b,
        0xe7, 0x06, 0x75, 0x00, 0x8d, 0x6f, 0x92, 0x74
    };
    const uint8_t integrity_key_s2c[] = {
        0x47, 0xd3, 0xc2, 0x0a, 0xba, 0x60, 0x98, 0x1e, 0x47, 0xb3, 0x05, 0x33,
        0x62, 0x36, 0x13, 0xff, 0x1c, 0xac, 0xbc, 0xf1, 0x64, 0x2f, 0xb4, 0xad,
        0x86, 0xee, 0x71, 0x2f, 0x2a, 0xed, 0x9a, 0xf8
    };

    uint8_t output[sizeof(integrity_key_c2s)] = {0};  // longest output

    // Initial IVs
    test_sshkdf(EVP_sha256(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
        output, sizeof(initial_iv_c2s),
        initial_iv_c2s);

    test_sshkdf(EVP_sha256(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_SRV_TO_CLI,
        output, sizeof(initial_iv_s2c),
        initial_iv_s2c);

    // Encryption keys
    test_sshkdf(EVP_sha256(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_CLI_TO_SRV,
        output, sizeof(encryption_key_c2s),
        encryption_key_c2s);

    test_sshkdf(EVP_sha256(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_SRV_TO_CLI,
        output, sizeof(encryption_key_s2c),
        encryption_key_s2c);

    // Integrity keys
    test_sshkdf(EVP_sha256(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_CLI_TO_SRV,
        output, sizeof(integrity_key_c2s),
        integrity_key_c2s);

    test_sshkdf(EVP_sha256(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_SRV_TO_CLI,
        output, sizeof(integrity_key_s2c),
        integrity_key_s2c);
}

TEST(SSHKDFTest, SSHKDF_SHA384) {
    const uint8_t key[] = {
        0x00, 0x00, 0x00, 0x81, 0x00, 0x94, 0x14, 0x56, 0xbd, 0x72, 0x26, 0x7a,
        0x90, 0x69, 0x0f, 0xfc, 0x87, 0x35, 0x28, 0xf4, 0xb7, 0x63, 0x94, 0x43,
        0x1a, 0xce, 0xee, 0x1e, 0x24, 0xa7, 0xbe, 0xd4, 0x14, 0x56, 0x8d, 0x9b,
        0x97, 0xc8, 0x4c, 0xe1, 0x3d, 0x34, 0xa2, 0xb4, 0xa6, 0x3e, 0xf7, 0x35,
        0xba, 0xc2, 0x3a, 0xf0, 0xb7, 0xfa, 0x63, 0x4a, 0x9e, 0x56, 0xc2, 0xd7,
        0x75, 0xc7, 0x41, 0xa6, 0x1d, 0x63, 0x98, 0x13, 0x32, 0xf9, 0x02, 0x7d,
        0x3f, 0x52, 0xc4, 0xa9, 0xa3, 0xad, 0xb8, 0x3e, 0x96, 0xd3, 0x9f, 0x7e,
        0x6b, 0xb7, 0x25, 0x14, 0x79, 0x7d, 0xa3, 0x2f, 0x2f, 0x0e, 0xdb, 0x59,
        0xac, 0xcf, 0xc5, 0x8a, 0x49, 0xfc, 0x34, 0xb1, 0x98, 0xe0, 0x28, 0x5b,
        0x31, 0x03, 0x2a, 0xc9, 0xf0, 0x69, 0x07, 0xde, 0xf1, 0x96, 0xf5, 0x74,
        0x8b, 0xd3, 0x2c, 0xe2, 0x2a, 0x53, 0x83, 0xa1, 0xbb, 0xdb, 0xd3, 0x1f,
        0x24
    };
    const uint8_t xcghash[] = {
        0xe0, 0xde, 0xe8, 0x0c, 0xcc, 0x16, 0x28, 0x84, 0x39, 0x39, 0x30, 0xad,
        0x20, 0x73, 0xd9, 0x21, 0x20, 0xc8, 0x04, 0x25, 0x41, 0x62, 0x44, 0x6b,
        0x7d, 0x04, 0x8f, 0x85, 0xa1, 0xa4, 0xdd, 0x7b, 0x63, 0x6a, 0x09, 0xb6,
        0x92, 0x52, 0xb8, 0x09, 0x52, 0xa0, 0x58, 0x1e, 0x94, 0x90, 0xee, 0x5a
    };
    const uint8_t session_id[] = {
        0xe0, 0xde, 0xe8, 0x0c, 0xcc, 0x16, 0x28, 0x84, 0x39, 0x39, 0x30, 0xad,
        0x20, 0x73, 0xd9, 0x21, 0x20, 0xc8, 0x04, 0x25, 0x41, 0x62, 0x44, 0x6b,
        0x7d, 0x04, 0x8f, 0x85, 0xa1, 0xa4, 0xdd, 0x7b, 0x63, 0x6a, 0x09, 0xb6,
        0x92, 0x52, 0xb8, 0x09, 0x52, 0xa0, 0x58, 0x1e, 0x94, 0x90, 0xee, 0x5a
    };

    const uint8_t initial_iv_c2s[] = {
        0xd3, 0x1c, 0x16, 0xf6, 0x7b, 0x17, 0xbc, 0x69
    };
    const uint8_t initial_iv_s2c[] = {
        0x67, 0x53, 0x40, 0xf2, 0x72, 0x69, 0xe7, 0xae
    };

    const uint8_t encryption_key_c2s[] = {
        0x2f, 0xfe, 0xd5, 0x77, 0xa9, 0x0d, 0x29, 0x87, 0x2e, 0xa5, 0x9f, 0x37,
        0x82, 0xc3, 0xb4, 0x06, 0x90, 0x8d, 0x73, 0x94, 0xff, 0x63, 0xc9, 0xd7
    };
    const uint8_t encryption_key_s2c[] = {
        0xfa, 0xe7, 0x51, 0x98, 0x7c, 0x1f, 0xa8, 0x66, 0x5e, 0x43, 0x87, 0xe4,
        0x10, 0x29, 0x7d, 0xb5, 0x8f, 0xf6, 0x9b, 0x26, 0x0a, 0x8f, 0xe8, 0x5f
    };

    const uint8_t integrity_key_c2s[] = {
        0xff, 0x2d, 0xb5, 0x97, 0x5e, 0xdf, 0x38, 0x24, 0x32, 0x5b, 0x25, 0x74,
        0x55, 0x79, 0x18, 0x69, 0x43, 0x4c, 0x6a, 0xf4, 0x7f, 0xb0, 0xc8, 0x14,
        0x52, 0x53, 0xc2, 0x69, 0x5a, 0xbf, 0xd2, 0xb8, 0xc9, 0x80, 0x56, 0x5a,
        0xd2, 0x0e, 0x6b, 0x93, 0x13, 0xba, 0x44, 0xee, 0x48, 0x8b, 0xaf, 0xb0
    };
    const uint8_t integrity_key_s2c[] = {
        0x85, 0xa9, 0x46, 0x3c, 0xd6, 0x53, 0xc7, 0x61, 0x9d, 0x4d, 0xc8, 0x50,
        0x06, 0x40, 0x6d, 0x6e, 0xd3, 0x36, 0x42, 0x20, 0x41, 0x9c, 0xa1, 0x38,
        0x10, 0x30, 0x1b, 0xe0, 0xf0, 0x38, 0x9d, 0x93, 0x2d, 0xde, 0xae, 0xbb,
        0x0e, 0x50, 0x4a, 0x08, 0x49, 0xe2, 0xe7, 0x3a, 0x7d, 0x08, 0x7d, 0xb2
    };

    uint8_t output[sizeof(integrity_key_c2s)] = {0};  // longest output

    // Initial IVs
    test_sshkdf(EVP_sha384(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
        output, sizeof(initial_iv_c2s),
        initial_iv_c2s);

    test_sshkdf(EVP_sha384(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_SRV_TO_CLI,
        output, sizeof(initial_iv_s2c),
        initial_iv_s2c);

    // Encryption keys
    test_sshkdf(EVP_sha384(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_CLI_TO_SRV,
        output, sizeof(encryption_key_c2s),
        encryption_key_c2s);

    test_sshkdf(EVP_sha384(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_SRV_TO_CLI,
        output, sizeof(encryption_key_s2c),
        encryption_key_s2c);

    // Integrity keys
    test_sshkdf(EVP_sha384(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_CLI_TO_SRV,
        output, sizeof(integrity_key_c2s),
        integrity_key_c2s);

    test_sshkdf(EVP_sha384(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_SRV_TO_CLI,
        output, sizeof(integrity_key_s2c),
        integrity_key_s2c);
}

TEST(SSHKDFTest, SSHKDF_SHA512) {
    const uint8_t key[] = {
        0x00, 0x00, 0x00, 0x80, 0x57, 0x53, 0x08, 0xca, 0x39, 0x57, 0x98, 0xbb,
        0x21, 0xec, 0x54, 0x38, 0xc4, 0x6a, 0x88, 0xff, 0xa3, 0xf7, 0xf7, 0x67,
        0x1c, 0x06, 0xf9, 0x24, 0xab, 0xf7, 0xc3, 0xcf, 0xb4, 0x6c, 0x78, 0xc0,
        0x25, 0x59, 0x6e, 0x4a, 0xba, 0x50, 0xc3, 0x27, 0x10, 0x89, 0x18, 0x4a,
        0x44, 0x7a, 0x57, 0x1a, 0xbb, 0x7f, 0x4a, 0x1b, 0x1c, 0x41, 0xf5, 0xd5,
        0xca, 0x80, 0x62, 0x94, 0x0d, 0x43, 0x69, 0x77, 0x85, 0x89, 0xfd, 0xe8,
        0x1a, 0x71, 0xb2, 0x22, 0x8f, 0x01, 0x8c, 0x4c, 0x83, 0x6c, 0xf3, 0x89,
        0xf8, 0x54, 0xf8, 0x6d, 0xe7, 0x1a, 0x68, 0xb1, 0x69, 0x3f, 0xe8, 0xff,
        0xa1, 0xc5, 0x9c, 0xe7, 0xe9, 0xf9, 0x22, 0x3d, 0xeb, 0xad, 0xa2, 0x56,
        0x6d, 0x2b, 0x0e, 0x56, 0x78, 0xa4, 0x8b, 0xfb, 0x53, 0x0e, 0x7b, 0xee,
        0x42, 0xbd, 0x2a, 0xc7, 0x30, 0x4a, 0x0a, 0x5a, 0xe3, 0x39, 0xa2, 0xcd
    };
    const uint8_t xcghash[] = {
        0xa4, 0x12, 0x5a, 0xa9, 0x89, 0x80, 0x92, 0xca, 0x50, 0xc3, 0xc1, 0x63,
        0x1c, 0x03, 0xdc, 0xbc, 0x9d, 0xf9, 0x5c, 0xeb, 0xb4, 0x09, 0x88, 0x1e,
        0x58, 0x01, 0x08, 0xb6, 0xcc, 0x47, 0x04, 0xb7, 0x6c, 0xc7, 0x7b, 0x87,
        0x95, 0xfd, 0x59, 0x40, 0x56, 0x1e, 0x32, 0x24, 0xcc, 0x75, 0x84, 0x85,
        0x18, 0x99, 0x2b, 0xd8, 0xd9, 0xb7, 0x0f, 0xe0, 0xfc, 0x97, 0x7a, 0x47,
        0x60, 0x63, 0xc8, 0xbf
    };
    const uint8_t session_id[] = {
        0xa4, 0x12, 0x5a, 0xa9, 0x89, 0x80, 0x92, 0xca, 0x50, 0xc3, 0xc1, 0x63,
        0x1c, 0x03, 0xdc, 0xbc, 0x9d, 0xf9, 0x5c, 0xeb, 0xb4, 0x09, 0x88, 0x1e,
        0x58, 0x01, 0x08, 0xb6, 0xcc, 0x47, 0x04, 0xb7, 0x6c, 0xc7, 0x7b, 0x87,
        0x95, 0xfd, 0x59, 0x40, 0x56, 0x1e, 0x32, 0x24, 0xcc, 0x75, 0x84, 0x85,
        0x18, 0x99, 0x2b, 0xd8, 0xd9, 0xb7, 0x0f, 0xe0, 0xfc, 0x97, 0x7a, 0x47,
        0x60, 0x63, 0xc8, 0xbf
    };

    const uint8_t initial_iv_c2s[] = {
        0x0e, 0x26, 0x93, 0xad, 0xe0, 0x52, 0x4a, 0xf8
    };
    const uint8_t initial_iv_s2c[] = {
        0xb1, 0x31, 0x44, 0xde, 0x02, 0x29, 0x5b, 0xb8
    };

    const uint8_t encryption_key_c2s[] = {
        0x7e, 0x4a, 0x72, 0x1f, 0xb7, 0x37, 0x9e, 0xbb, 0x42, 0x33, 0x06, 0x46,
        0x4d, 0x57, 0xdb, 0x46, 0xaf, 0xa3, 0xcc, 0xa1, 0x0a, 0x1d, 0x7f, 0xeb
    };
    const uint8_t encryption_key_s2c[] = {
        0xbb, 0x84, 0x12, 0x3b, 0x1f, 0xac, 0x40, 0x0e, 0x0d, 0xf4, 0x76, 0x7d,
        0x78, 0xd0, 0x11, 0x42, 0x7e, 0x1e, 0xdd, 0x4d, 0x4c, 0x93, 0x4b, 0x95
    };

    const uint8_t integrity_key_c2s[] = {
        0x00, 0xfb, 0x0a, 0x45, 0xc6, 0x50, 0xdd, 0x9c, 0x95, 0x66, 0x6b, 0x0c,
        0x7f, 0xce, 0xa8, 0xc9, 0x8f, 0x05, 0x62, 0xf6, 0x1b, 0x86, 0x20, 0x54,
        0xee, 0x40, 0x0a, 0xec, 0x87, 0x5d, 0xbb, 0xc2, 0xbd, 0xef, 0x48, 0x06,
        0xc0, 0x92, 0x17, 0x70, 0x9a, 0x50, 0x50, 0x56, 0x93, 0x12, 0xef, 0xe3,
        0xaf, 0x51, 0x3e, 0x7a, 0xa7, 0x33, 0xc7, 0x24, 0x57, 0xab, 0xe1, 0x60,
        0x7a, 0xc0, 0x1c, 0x13
    };
    const uint8_t integrity_key_s2c[] = {
        0x70, 0xa8, 0x00, 0x5e, 0x71, 0x1f, 0xb9, 0x6d, 0xea, 0x59, 0x91, 0xcb,
        0x68, 0x83, 0x1b, 0x9e, 0x86, 0x00, 0x58, 0x21, 0xb4, 0x5c, 0xea, 0xf9,
        0x58, 0xc1, 0x3d, 0x5c, 0x87, 0xcb, 0xd2, 0x95, 0x3d, 0x08, 0x77, 0xc2,
        0x67, 0x79, 0x6e, 0xdf, 0x8c, 0x7f, 0xb3, 0xd7, 0x68, 0xbb, 0x26, 0xb7,
        0x4e, 0x54, 0x2f, 0x40, 0xbf, 0x9a, 0xc9, 0xf6, 0xa9, 0xd2, 0x17, 0x07,
        0x7e, 0x85, 0xf5, 0x11
    };

    uint8_t output[sizeof(integrity_key_c2s)] = {0};  // longest output

    // Initial IVs
    test_sshkdf(EVP_sha512(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_CLI_TO_SRV,
        output, sizeof(initial_iv_c2s),
        initial_iv_c2s);

    test_sshkdf(EVP_sha512(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INITIAL_IV_SRV_TO_CLI,
        output, sizeof(initial_iv_s2c),
        initial_iv_s2c);

    // Encryption keys
    test_sshkdf(EVP_sha512(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_CLI_TO_SRV,
        output, sizeof(encryption_key_c2s),
        encryption_key_c2s);

    test_sshkdf(EVP_sha512(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_ENCRYPTION_KEY_SRV_TO_CLI,
        output, sizeof(encryption_key_s2c),
        encryption_key_s2c);

    // Integrity keys
    test_sshkdf(EVP_sha512(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_CLI_TO_SRV,
        output, sizeof(integrity_key_c2s),
        integrity_key_c2s);

    test_sshkdf(EVP_sha512(), key, sizeof(key), xcghash, sizeof(xcghash),
        session_id, sizeof(session_id),
        EVP_KDF_SSHKDF_TYPE_INTEGRITY_KEY_SRV_TO_CLI,
        output, sizeof(integrity_key_s2c),
        integrity_key_s2c);
}
