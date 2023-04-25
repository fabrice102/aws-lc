/* Copyright (c) 2015, Google Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

 /* This file was generated by err_data_generate.go. */

#include <openssl/base.h>
#include <openssl/err.h>
#include <openssl/type_check.h>


OPENSSL_STATIC_ASSERT(ERR_LIB_NONE == 1, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_SYS == 2, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_BN == 3, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_RSA == 4, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_DH == 5, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_EVP == 6, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_BUF == 7, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_OBJ == 8, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_PEM == 9, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_DSA == 10, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_X509 == 11, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_ASN1 == 12, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_CONF == 13, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_CRYPTO == 14, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_EC == 15, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_SSL == 16, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_BIO == 17, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_PKCS7 == 18, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_PKCS8 == 19, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_X509V3 == 20, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_RAND == 21, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_ENGINE == 22, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_OCSP == 23, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_UI == 24, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_COMP == 25, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_ECDSA == 26, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_ECDH == 27, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_HMAC == 28, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_DIGEST == 29, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_CIPHER == 30, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_HKDF == 31, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_TRUST_TOKEN == 32, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_LIB_USER == 33, library_value_changed)
OPENSSL_STATIC_ASSERT(ERR_NUM_LIBS == 34, number_of_libraries_changed)

const uint32_t kOpenSSLReasonValues[] = {
    0xc320885,
    0xc32889f,
    0xc3308ae,
    0xc3388be,
    0xc3408cd,
    0xc3488e6,
    0xc3508f2,
    0xc35890f,
    0xc36092f,
    0xc36893d,
    0xc37094d,
    0xc37895a,
    0xc38096a,
    0xc388975,
    0xc39098b,
    0xc39899a,
    0xc3a09ae,
    0xc3a8892,
    0xc3b00f7,
    0xc3b8921,
    0x10320892,
    0x103298fe,
    0x1033190a,
    0x10339923,
    0x10341936,
    0x10348fe1,
    0x10350d1a,
    0x10359949,
    0x10361973,
    0x10369986,
    0x103719a5,
    0x103799be,
    0x103819d3,
    0x103899f1,
    0x10391a00,
    0x10399a1c,
    0x103a1a37,
    0x103a9a46,
    0x103b1a62,
    0x103b9a7d,
    0x103c1aa3,
    0x103c80f7,
    0x103d1ab4,
    0x103d9ac8,
    0x103e1ae7,
    0x103e9af6,
    0x103f1b0d,
    0x103f9b20,
    0x10400cde,
    0x10409b33,
    0x10411b51,
    0x10419b64,
    0x10421b7e,
    0x10429b8e,
    0x10431ba2,
    0x10439bb8,
    0x10441bd0,
    0x10449be5,
    0x10451bf9,
    0x10459c0b,
    0x10460635,
    0x1046899a,
    0x10471c20,
    0x10479c37,
    0x10481c4c,
    0x10489c5a,
    0x10490f2d,
    0x10499a94,
    0x104a195e,
    0x107c0fef,
    0x14320cc1,
    0x14328ccf,
    0x14330cde,
    0x14338cf0,
    0x143400b9,
    0x143480f7,
    0x18320090,
    0x1832904c,
    0x183300b9,
    0x18339062,
    0x18341076,
    0x183480f7,
    0x18351095,
    0x183590ad,
    0x183610c2,
    0x183690d6,
    0x1837110e,
    0x18379124,
    0x18381138,
    0x18389148,
    0x18390add,
    0x18399158,
    0x183a118d,
    0x183a91e2,
    0x183b0d39,
    0x183b9231,
    0x183c1243,
    0x183c924e,
    0x183d125e,
    0x183d926f,
    0x183e1280,
    0x183e9292,
    0x183f12bb,
    0x183f92d4,
    0x184012ec,
    0x1840870d,
    0x18411205,
    0x184191d0,
    0x184211ef,
    0x18428d26,
    0x1843116d,
    0x18439217,
    0x1844108b,
    0x184490fa,
    0x184509e0,
    0x18fa117e,
    0x18fa91a1,
    0x18fb11b6,
    0x20321326,
    0x20329313,
    0x24321534,
    0x243289e0,
    0x24331546,
    0x24339553,
    0x24341560,
    0x24349572,
    0x24351581,
    0x2435959e,
    0x243615ab,
    0x243695b9,
    0x243715c7,
    0x243795ef,
    0x243815f8,
    0x24389605,
    0x24391618,
    0x243995d5,
    0x28320d0e,
    0x28328d39,
    0x28330cde,
    0x28338d4c,
    0x28340d1a,
    0x283480b9,
    0x283500f7,
    0x28358d26,
    0x2836099a,
    0x2c32365b,
    0x2c32962f,
    0x2c333669,
    0x2c33b67b,
    0x2c34368f,
    0x2c34b6a1,
    0x2c3536bc,
    0x2c35b6ce,
    0x2c3636fe,
    0x2c36833a,
    0x2c37370b,
    0x2c37b737,
    0x2c383775,
    0x2c38b78c,
    0x2c3937aa,
    0x2c39b7ba,
    0x2c3a37cc,
    0x2c3ab7e0,
    0x2c3b37f1,
    0x2c3bb810,
    0x2c3c1641,
    0x2c3c9657,
    0x2c3d3855,
    0x2c3d9670,
    0x2c3e387f,
    0x2c3eb88d,
    0x2c3f38a5,
    0x2c3fb8bd,
    0x2c4038e7,
    0x2c409326,
    0x2c4138f8,
    0x2c41b90b,
    0x2c4212ec,
    0x2c42b91c,
    0x2c43076d,
    0x2c43b802,
    0x2c44374a,
    0x2c44b8ca,
    0x2c4536e1,
    0x2c45b71d,
    0x2c46379a,
    0x2c46b824,
    0x2c473839,
    0x2c47b872,
    0x2c48375c,
    0x30320000,
    0x30328015,
    0x3033001f,
    0x30338038,
    0x30340057,
    0x30348071,
    0x30350078,
    0x30358090,
    0x303600a1,
    0x303680b9,
    0x303700c6,
    0x303780d5,
    0x303800f7,
    0x30388104,
    0x30390117,
    0x30398132,
    0x303a0147,
    0x303a815b,
    0x303b016f,
    0x303b8180,
    0x303c0199,
    0x303c81b6,
    0x303d01c4,
    0x303d81d8,
    0x303e01e8,
    0x303e8201,
    0x303f0211,
    0x303f8224,
    0x30400233,
    0x3040823f,
    0x30410254,
    0x30418264,
    0x3042027b,
    0x30428288,
    0x3043029b,
    0x304382aa,
    0x304402bf,
    0x304482e0,
    0x304502f3,
    0x30458306,
    0x3046031f,
    0x3046833a,
    0x30470372,
    0x30478384,
    0x304803a2,
    0x304883b3,
    0x304903c2,
    0x304983da,
    0x304a03ec,
    0x304a8400,
    0x304b0418,
    0x304b842b,
    0x304c0436,
    0x304c8447,
    0x304d0453,
    0x304d8469,
    0x304e0477,
    0x304e848d,
    0x304f049f,
    0x304f84b1,
    0x305004d4,
    0x305084e7,
    0x305104f8,
    0x30518508,
    0x30520520,
    0x30528535,
    0x3053054d,
    0x30538561,
    0x30540579,
    0x30548592,
    0x305505ab,
    0x305585c8,
    0x305605d3,
    0x305685eb,
    0x305705fb,
    0x3057860c,
    0x3058061f,
    0x30588635,
    0x3059063e,
    0x30598653,
    0x305a0666,
    0x305a8675,
    0x305b0695,
    0x305b86a4,
    0x305c06c5,
    0x305c86e1,
    0x305d06ed,
    0x305d870d,
    0x305e0729,
    0x305e874d,
    0x305f0763,
    0x305f876d,
    0x306004c4,
    0x3060804a,
    0x30610357,
    0x3061873a,
    0x30620392,
    0x34320c1f,
    0x34328c33,
    0x34330c50,
    0x34338c63,
    0x34340c72,
    0x34348cab,
    0x34350c8f,
    0x3c320090,
    0x3c328d76,
    0x3c330d8f,
    0x3c338daa,
    0x3c340dc7,
    0x3c348df1,
    0x3c350e0c,
    0x3c358e32,
    0x3c360e4b,
    0x3c368e63,
    0x3c370e74,
    0x3c378e82,
    0x3c380e8f,
    0x3c388ea3,
    0x3c390d39,
    0x3c398ec6,
    0x3c3a0eda,
    0x3c3a895a,
    0x3c3b0eea,
    0x3c3b8f05,
    0x3c3c0f17,
    0x3c3c8f4a,
    0x3c3d0f54,
    0x3c3d8f68,
    0x3c3e0f76,
    0x3c3e8f9b,
    0x3c3f0d62,
    0x3c3f8f84,
    0x3c4000b9,
    0x3c4080f7,
    0x3c410de2,
    0x3c418e21,
    0x3c420f2d,
    0x3c428eb7,
    0x40321cec,
    0x40329d02,
    0x40331d30,
    0x40339d3a,
    0x40341d51,
    0x40349d6f,
    0x40351d7f,
    0x40359d91,
    0x40361d9e,
    0x40369daa,
    0x40371dbf,
    0x40379dd1,
    0x40381ddc,
    0x40389dee,
    0x40390fe1,
    0x40399dfe,
    0x403a1e11,
    0x403a9e32,
    0x403b1e43,
    0x403b9e53,
    0x403c0071,
    0x403c8090,
    0x403d1eb4,
    0x403d9eca,
    0x403e1ed9,
    0x403e9f11,
    0x403f1f2b,
    0x403f9f53,
    0x40401f68,
    0x40409f7c,
    0x40411fb7,
    0x40419fd2,
    0x40421feb,
    0x40429ffe,
    0x40432012,
    0x4043a040,
    0x40442057,
    0x404480b9,
    0x4045206c,
    0x4045a07e,
    0x404620a2,
    0x4046a0c2,
    0x404720d0,
    0x4047a0f7,
    0x40482168,
    0x4048a222,
    0x40492239,
    0x4049a253,
    0x404a226a,
    0x404aa288,
    0x404b22a0,
    0x404ba2cd,
    0x404c22e3,
    0x404ca2f5,
    0x404d2316,
    0x404da34f,
    0x404e2363,
    0x404ea370,
    0x404f240a,
    0x404fa480,
    0x405024ef,
    0x4050a503,
    0x40512536,
    0x40522546,
    0x4052a56a,
    0x40532582,
    0x4053a595,
    0x405425aa,
    0x4054a5cd,
    0x405525f8,
    0x4055a635,
    0x4056265a,
    0x4056a673,
    0x4057268b,
    0x4057a69e,
    0x405826b3,
    0x4058a6da,
    0x40592709,
    0x4059a736,
    0x405a274a,
    0x405aa75a,
    0x405b2772,
    0x405ba783,
    0x405c2796,
    0x405ca7d5,
    0x405d27e2,
    0x405da807,
    0x405e2845,
    0x405e8b1b,
    0x405f2866,
    0x405fa873,
    0x40602881,
    0x4060a8a3,
    0x40612904,
    0x4061a93c,
    0x40622953,
    0x4062a964,
    0x406329b1,
    0x4063a9c6,
    0x406429dd,
    0x4064aa09,
    0x40652a24,
    0x4065aa3b,
    0x40662a53,
    0x4066aa7d,
    0x40672aa8,
    0x4067abab,
    0x40682bf3,
    0x4068ac14,
    0x40692c46,
    0x4069ac74,
    0x406a2c95,
    0x406aacb5,
    0x406b2e3d,
    0x406bae60,
    0x406c2e76,
    0x406cb180,
    0x406d31af,
    0x406db1d7,
    0x406e3205,
    0x406eb252,
    0x406f32ab,
    0x406fb2e3,
    0x407032f6,
    0x4070b313,
    0x4071084d,
    0x4071b325,
    0x40723338,
    0x4072b36e,
    0x40733386,
    0x40739859,
    0x4074339a,
    0x4074b3b4,
    0x407533c5,
    0x4075b3d9,
    0x407633e7,
    0x40769605,
    0x4077340c,
    0x4077b44c,
    0x40783467,
    0x4078b4a0,
    0x407934b7,
    0x4079b4cd,
    0x407a34f9,
    0x407ab50c,
    0x407b3521,
    0x407bb533,
    0x407c3564,
    0x407cb56d,
    0x407d2c2f,
    0x407da4a8,
    0x407e347c,
    0x407ea6ea,
    0x407f20e4,
    0x407fa2b7,
    0x4080241a,
    0x4080a10c,
    0x40812558,
    0x4081a3be,
    0x408231f0,
    0x40829e5f,
    0x408326c5,
    0x4083a9ee,
    0x40842120,
    0x4084a722,
    0x408527a7,
    0x4085a8cb,
    0x40862827,
    0x4086a4c2,
    0x40873236,
    0x4087a919,
    0x40881e9d,
    0x4088abbe,
    0x40891eec,
    0x40899e79,
    0x408a2eae,
    0x408a9c71,
    0x408b3548,
    0x408bb2c0,
    0x408c27b7,
    0x408c9ca9,
    0x408d2208,
    0x408da152,
    0x408e2338,
    0x408ea615,
    0x408f2bd2,
    0x408fa8e7,
    0x40902ac9,
    0x4090a7f9,
    0x40912e96,
    0x40919ccf,
    0x40921f39,
    0x4092b271,
    0x40933351,
    0x4093a4d3,
    0x40942134,
    0x4094aec7,
    0x40952975,
    0x4095b4d9,
    0x4096321d,
    0x4096a433,
    0x4097251e,
    0x4097a387,
    0x40981f99,
    0x4098a989,
    0x4099328d,
    0x4099a642,
    0x409a25db,
    0x409a9c8d,
    0x409b218e,
    0x409ba1b9,
    0x409c342e,
    0x409ca1e1,
    0x409d23ef,
    0x409da3d4,
    0x409e202a,
    0x409ea468,
    0x409f2450,
    0x409fa181,
    0x40a02490,
    0x40a0a3a1,
    0x40fa2b91,
    0x40faaaed,
    0x40fb2b70,
    0x40fbab07,
    0x40fcab4f,
    0x40fd2b28,
    0x41f42d68,
    0x41f92dfa,
    0x41fe2ced,
    0x41feafa3,
    0x41ff30d1,
    0x42032d81,
    0x42082da3,
    0x4208addf,
    0x42092cd1,
    0x4209ae19,
    0x420a2d28,
    0x420aad08,
    0x420b2d48,
    0x420badc1,
    0x420c30ed,
    0x420caed7,
    0x420d2f8a,
    0x420dafc1,
    0x42122ff4,
    0x421730b4,
    0x4217b036,
    0x421c3058,
    0x421f3013,
    0x42213165,
    0x42263097,
    0x422b3143,
    0x422baf65,
    0x422c3125,
    0x422caf18,
    0x422d2ef1,
    0x422db104,
    0x422e2f44,
    0x42303073,
    0x4230afdb,
    0x44320778,
    0x44328787,
    0x44330793,
    0x443387a1,
    0x443407b4,
    0x443487c5,
    0x443507cc,
    0x443587d6,
    0x443607e9,
    0x443687ff,
    0x44370811,
    0x4437881e,
    0x4438082d,
    0x44388835,
    0x4439084d,
    0x4439885b,
    0x443a086e,
    0x4832162f,
    0x48329641,
    0x48331657,
    0x48339670,
    0x4c3216ad,
    0x4c3296bd,
    0x4c3316d0,
    0x4c3396f0,
    0x4c3400b9,
    0x4c3480f7,
    0x4c3516fc,
    0x4c35970a,
    0x4c361726,
    0x4c36974c,
    0x4c37175b,
    0x4c379769,
    0x4c38177e,
    0x4c38978a,
    0x4c3917aa,
    0x4c3997d4,
    0x4c3a17ed,
    0x4c3a9806,
    0x4c3b0635,
    0x4c3b981f,
    0x4c3c1831,
    0x4c3c9840,
    0x4c3d1859,
    0x4c3d8d01,
    0x4c3e18c6,
    0x4c3e9868,
    0x4c3f18e8,
    0x4c3f9605,
    0x4c40187e,
    0x4c409699,
    0x4c4118b6,
    0x4c419739,
    0x4c4218a2,
    0x4c429681,
    0x5032392e,
    0x5032b93d,
    0x50333948,
    0x5033b958,
    0x50343971,
    0x5034b98b,
    0x50353999,
    0x5035b9af,
    0x503639c1,
    0x5036b9d7,
    0x503739f0,
    0x5037ba03,
    0x50383a1b,
    0x5038ba2c,
    0x50393a41,
    0x5039ba55,
    0x503a3a75,
    0x503aba8b,
    0x503b3aa3,
    0x503bbab5,
    0x503c3ad1,
    0x503cbae8,
    0x503d3b01,
    0x503dbb17,
    0x503e3b24,
    0x503ebb3a,
    0x503f3b4c,
    0x503f83b3,
    0x50403b5f,
    0x5040bb6f,
    0x50413b89,
    0x5041bb98,
    0x50423bb2,
    0x5042bbcf,
    0x50433bdf,
    0x5043bbef,
    0x50443c0c,
    0x50448469,
    0x50453c20,
    0x5045bc3e,
    0x50463c51,
    0x5046bc67,
    0x50473c79,
    0x5047bc8e,
    0x50483cb4,
    0x5048bcc2,
    0x50493cd5,
    0x5049bcea,
    0x504a3d00,
    0x504abd10,
    0x504b3d30,
    0x504bbd43,
    0x504c3d66,
    0x504cbd94,
    0x504d3dc1,
    0x504dbdde,
    0x504e3df9,
    0x504ebe15,
    0x504f3e27,
    0x504fbe3e,
    0x50503e4d,
    0x50508729,
    0x50513e60,
    0x5051bbfe,
    0x50523da6,
    0x58321034,
    0x5c329332,
    0x5c33134b,
    0x5c33939c,
    0x5c3413d3,
    0x5c3493e6,
    0x5c3613ff,
    0x5c37143f,
    0x5c379466,
    0x5c38148b,
    0x5c39949f,
    0x5c3a94bb,
    0x5c3b14cd,
    0x5c3b951d,
    0x5c3c1326,
    0x5c3c938a,
    0x5c3d1356,
    0x5c3d9370,
    0x5c3e13b6,
    0x5c3e94ea,
    0x5c3f14f9,
    0x5c3f950e,
    0x5c411410,
    0x5c41941e,
    0x68320fe1,
    0x68328d39,
    0x68330d4c,
    0x68339004,
    0x68341014,
    0x683480f7,
    0x6835099a,
    0x68668fef,
    0x6c320fa7,
    0x6c328cf0,
    0x6c330fb2,
    0x6c338fcb,
    0x74320a83,
    0x743280b9,
    0x74330d01,
    0x783209cb,
    0x783289e0,
    0x783309ec,
    0x78338090,
    0x783409fb,
    0x78348a10,
    0x78350a4c,
    0x78358a6e,
    0x78360a83,
    0x78368a99,
    0x78370aa9,
    0x78378aca,
    0x78380add,
    0x78388aef,
    0x78390afc,
    0x78398b1b,
    0x783a0b53,
    0x783a8b61,
    0x783b0b6b,
    0x783b8b7f,
    0x783c0b96,
    0x783c8bab,
    0x783d0bc2,
    0x783d8bd7,
    0x783e0b0a,
    0x783e8abc,
    0x78450c0b,
    0x78458bf0,
    0x78460a2f,
    0x78468b30,
    0x7c321302,
    0x8032174c,
    0x80328090,
    0x8033362a,
    0x803380b9,
    0x80343639,
    0x8034b5a1,
    0x803535bf,
    0x8035b64d,
    0x80363601,
    0x8036b5b0,
    0x803735f3,
    0x8037b58e,
    0x80383614,
    0x8038b5d0,
    0x803935e5,
};

const size_t kOpenSSLReasonValuesLen = sizeof(kOpenSSLReasonValues) / sizeof(kOpenSSLReasonValues[0]);

const char kOpenSSLReasonStringData[] =
    "ASN1_LENGTH_MISMATCH\0"
    "AUX_ERROR\0"
    "BAD_GET_ASN1_OBJECT_CALL\0"
    "BAD_OBJECT_HEADER\0"
    "BAD_TEMPLATE\0"
    "BMPSTRING_IS_WRONG_LENGTH\0"
    "BN_LIB\0"
    "BOOLEAN_IS_WRONG_LENGTH\0"
    "BUFFER_TOO_SMALL\0"
    "CONTEXT_NOT_INITIALISED\0"
    "DECODE_ERROR\0"
    "DEPTH_EXCEEDED\0"
    "DIGEST_AND_KEY_TYPE_NOT_SUPPORTED\0"
    "ENCODE_ERROR\0"
    "ERROR_GETTING_TIME\0"
    "EXPECTING_AN_ASN1_SEQUENCE\0"
    "EXPECTING_AN_INTEGER\0"
    "EXPECTING_AN_OBJECT\0"
    "EXPECTING_A_BOOLEAN\0"
    "EXPECTING_A_TIME\0"
    "EXPLICIT_LENGTH_MISMATCH\0"
    "EXPLICIT_TAG_NOT_CONSTRUCTED\0"
    "FIELD_MISSING\0"
    "FIRST_NUM_TOO_LARGE\0"
    "HEADER_TOO_LONG\0"
    "ILLEGAL_BITSTRING_FORMAT\0"
    "ILLEGAL_BOOLEAN\0"
    "ILLEGAL_CHARACTERS\0"
    "ILLEGAL_FORMAT\0"
    "ILLEGAL_HEX\0"
    "ILLEGAL_IMPLICIT_TAG\0"
    "ILLEGAL_INTEGER\0"
    "ILLEGAL_NESTED_TAGGING\0"
    "ILLEGAL_NULL\0"
    "ILLEGAL_NULL_VALUE\0"
    "ILLEGAL_OBJECT\0"
    "ILLEGAL_OPTIONAL_ANY\0"
    "ILLEGAL_OPTIONS_ON_ITEM_TEMPLATE\0"
    "ILLEGAL_TAGGED_ANY\0"
    "ILLEGAL_TIME_VALUE\0"
    "INTEGER_NOT_ASCII_FORMAT\0"
    "INTEGER_TOO_LARGE_FOR_LONG\0"
    "INVALID_BIT_STRING_BITS_LEFT\0"
    "INVALID_BIT_STRING_PADDING\0"
    "INVALID_BMPSTRING\0"
    "INVALID_DIGIT\0"
    "INVALID_INTEGER\0"
    "INVALID_MODIFIER\0"
    "INVALID_NUMBER\0"
    "INVALID_OBJECT_ENCODING\0"
    "INVALID_SEPARATOR\0"
    "INVALID_TIME_FORMAT\0"
    "INVALID_UNIVERSALSTRING\0"
    "INVALID_UTF8STRING\0"
    "LIST_ERROR\0"
    "MISSING_ASN1_EOS\0"
    "MISSING_EOC\0"
    "MISSING_SECOND_NUMBER\0"
    "MISSING_VALUE\0"
    "MSTRING_NOT_UNIVERSAL\0"
    "MSTRING_WRONG_TAG\0"
    "NESTED_ASN1_ERROR\0"
    "NESTED_ASN1_STRING\0"
    "NESTED_TOO_DEEP\0"
    "NON_HEX_CHARACTERS\0"
    "NOT_ASCII_FORMAT\0"
    "NOT_ENOUGH_DATA\0"
    "NO_MATCHING_CHOICE_TYPE\0"
    "NULL_IS_WRONG_LENGTH\0"
    "OBJECT_NOT_ASCII_FORMAT\0"
    "ODD_NUMBER_OF_CHARS\0"
    "SECOND_NUMBER_TOO_LARGE\0"
    "SEQUENCE_LENGTH_MISMATCH\0"
    "SEQUENCE_NOT_CONSTRUCTED\0"
    "SEQUENCE_OR_SET_NEEDS_CONFIG\0"
    "SHORT_LINE\0"
    "STREAMING_NOT_SUPPORTED\0"
    "STRING_TOO_LONG\0"
    "STRING_TOO_SHORT\0"
    "TAG_VALUE_TOO_HIGH\0"
    "TIME_NOT_ASCII_FORMAT\0"
    "TOO_LONG\0"
    "TYPE_NOT_CONSTRUCTED\0"
    "TYPE_NOT_PRIMITIVE\0"
    "UNEXPECTED_EOC\0"
    "UNIVERSALSTRING_IS_WRONG_LENGTH\0"
    "UNKNOWN_FORMAT\0"
    "UNKNOWN_MESSAGE_DIGEST_ALGORITHM\0"
    "UNKNOWN_SIGNATURE_ALGORITHM\0"
    "UNKNOWN_TAG\0"
    "UNSUPPORTED_ANY_DEFINED_BY_TYPE\0"
    "UNSUPPORTED_PUBLIC_KEY_TYPE\0"
    "UNSUPPORTED_TYPE\0"
    "WRONG_INTEGER_TYPE\0"
    "WRONG_PUBLIC_KEY_TYPE\0"
    "WRONG_TAG\0"
    "WRONG_TYPE\0"
    "BAD_FOPEN_MODE\0"
    "BROKEN_PIPE\0"
    "CONNECT_ERROR\0"
    "ERROR_SETTING_NBIO\0"
    "INVALID_ARGUMENT\0"
    "IN_USE\0"
    "KEEPALIVE\0"
    "NBIO_CONNECT_ERROR\0"
    "NO_HOSTNAME_SPECIFIED\0"
    "NO_PORT_SPECIFIED\0"
    "NO_SUCH_FILE\0"
    "NULL_PARAMETER\0"
    "SYS_LIB\0"
    "UNABLE_TO_CREATE_SOCKET\0"
    "UNINITIALIZED\0"
    "UNSUPPORTED_METHOD\0"
    "WRITE_TO_READ_ONLY_BIO\0"
    "ARG2_LT_ARG3\0"
    "BAD_ENCODING\0"
    "BAD_RECIPROCAL\0"
    "BIGNUM_TOO_LONG\0"
    "BITS_TOO_SMALL\0"
    "CALLED_WITH_EVEN_MODULUS\0"
    "DIV_BY_ZERO\0"
    "EXPAND_ON_STATIC_BIGNUM_DATA\0"
    "INPUT_NOT_REDUCED\0"
    "INVALID_INPUT\0"
    "INVALID_RANGE\0"
    "NEGATIVE_NUMBER\0"
    "NOT_A_SQUARE\0"
    "NOT_INITIALIZED\0"
    "NO_INVERSE\0"
    "PRIVATE_KEY_TOO_LARGE\0"
    "P_IS_NOT_PRIME\0"
    "TOO_MANY_ITERATIONS\0"
    "TOO_MANY_TEMPORARY_VARIABLES\0"
    "AES_KEY_SETUP_FAILED\0"
    "BAD_DECRYPT\0"
    "BAD_KEY_LENGTH\0"
    "CTRL_NOT_IMPLEMENTED\0"
    "CTRL_OPERATION_NOT_IMPLEMENTED\0"
    "CTRL_OPERATION_NOT_PERFORMED\0"
    "DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH\0"
    "INITIALIZATION_ERROR\0"
    "INPUT_NOT_INITIALIZED\0"
    "INVALID_AD_SIZE\0"
    "INVALID_KEY_LENGTH\0"
    "INVALID_NONCE\0"
    "INVALID_NONCE_SIZE\0"
    "INVALID_OPERATION\0"
    "IV_TOO_LARGE\0"
    "NO_CIPHER_SET\0"
    "NO_DIRECTION_SET\0"
    "OUTPUT_ALIASES_INPUT\0"
    "SERIALIZATION_INVALID_EVP_AEAD_CTX\0"
    "TAG_TOO_LARGE\0"
    "TOO_LARGE\0"
    "UNSUPPORTED_AD_SIZE\0"
    "UNSUPPORTED_INPUT_SIZE\0"
    "UNSUPPORTED_KEY_SIZE\0"
    "UNSUPPORTED_NONCE_SIZE\0"
    "UNSUPPORTED_TAG_SIZE\0"
    "WRONG_FINAL_BLOCK_LENGTH\0"
    "XTS_DATA_UNIT_IS_TOO_LARGE\0"
    "XTS_DUPLICATED_KEYS\0"
    "LIST_CANNOT_BE_NULL\0"
    "MISSING_CLOSE_SQUARE_BRACKET\0"
    "MISSING_EQUAL_SIGN\0"
    "NO_CLOSE_BRACE\0"
    "UNABLE_TO_CREATE_NEW_SECTION\0"
    "VARIABLE_EXPANSION_TOO_LONG\0"
    "VARIABLE_HAS_NO_VALUE\0"
    "BAD_GENERATOR\0"
    "INVALID_PUBKEY\0"
    "MODULUS_TOO_LARGE\0"
    "NO_PRIVATE_VALUE\0"
    "UNKNOWN_HASH\0"
    "BAD_Q_VALUE\0"
    "BAD_VERSION\0"
    "INVALID_PARAMETERS\0"
    "MISSING_PARAMETERS\0"
    "NEED_NEW_SETUP_VALUES\0"
    "BIGNUM_OUT_OF_RANGE\0"
    "COORDINATES_OUT_OF_RANGE\0"
    "D2I_ECPKPARAMETERS_FAILURE\0"
    "EC_GROUP_NEW_BY_NAME_FAILURE\0"
    "GROUP2PKPARAMETERS_FAILURE\0"
    "GROUP_MISMATCH\0"
    "I2D_ECPKPARAMETERS_FAILURE\0"
    "INCOMPATIBLE_OBJECTS\0"
    "INVALID_COFACTOR\0"
    "INVALID_COMPRESSED_POINT\0"
    "INVALID_COMPRESSION_BIT\0"
    "INVALID_ENCODING\0"
    "INVALID_FIELD\0"
    "INVALID_FORM\0"
    "INVALID_GROUP_ORDER\0"
    "INVALID_PRIVATE_KEY\0"
    "INVALID_SCALAR\0"
    "MISSING_PRIVATE_KEY\0"
    "NON_NAMED_CURVE\0"
    "PKPARAMETERS2GROUP_FAILURE\0"
    "POINT_AT_INFINITY\0"
    "POINT_IS_NOT_ON_CURVE\0"
    "PUBLIC_KEY_VALIDATION_FAILED\0"
    "SLOT_FULL\0"
    "UNDEFINED_GENERATOR\0"
    "UNKNOWN_GROUP\0"
    "UNKNOWN_ORDER\0"
    "WRONG_CURVE_PARAMETERS\0"
    "WRONG_ORDER\0"
    "KDF_FAILED\0"
    "POINT_ARITHMETIC_FAILURE\0"
    "UNKNOWN_DIGEST_LENGTH\0"
    "BAD_SIGNATURE\0"
    "MISMATCHED_SIGNATURE\0"
    "NOT_IMPLEMENTED\0"
    "RANDOM_NUMBER_GENERATION_FAILED\0"
    "OPERATION_NOT_SUPPORTED\0"
    "COMMAND_NOT_SUPPORTED\0"
    "DIFFERENT_KEY_TYPES\0"
    "DIFFERENT_PARAMETERS\0"
    "EMPTY_PSK\0"
    "EXPECTING_AN_EC_KEY_KEY\0"
    "EXPECTING_AN_RSA_KEY\0"
    "EXPECTING_A_DSA_KEY\0"
    "ILLEGAL_OR_UNSUPPORTED_PADDING_MODE\0"
    "INVALID_BUFFER_SIZE\0"
    "INVALID_DIGEST_LENGTH\0"
    "INVALID_DIGEST_TYPE\0"
    "INVALID_KEYBITS\0"
    "INVALID_MGF1_MD\0"
    "INVALID_PADDING_MODE\0"
    "INVALID_PEER_KEY\0"
    "INVALID_PSS_MD\0"
    "INVALID_PSS_SALTLEN\0"
    "INVALID_PSS_SALT_LEN\0"
    "INVALID_PSS_TRAILER_FIELD\0"
    "INVALID_SIGNATURE\0"
    "KEYS_NOT_SET\0"
    "MEMORY_LIMIT_EXCEEDED\0"
    "NOT_A_PRIVATE_KEY\0"
    "NOT_XOF_OR_INVALID_LENGTH\0"
    "NO_DEFAULT_DIGEST\0"
    "NO_KEY_SET\0"
    "NO_MDC2_SUPPORT\0"
    "NO_NID_FOR_CURVE\0"
    "NO_OPERATION_SET\0"
    "NO_PARAMETERS_SET\0"
    "OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE\0"
    "OPERATON_NOT_INITIALIZED\0"
    "UNKNOWN_PUBLIC_KEY_TYPE\0"
    "UNSUPPORTED_ALGORITHM\0"
    "OUTPUT_TOO_LARGE\0"
    "INVALID_OID_STRING\0"
    "UNKNOWN_NID\0"
    "CERTIFICATE_VERIFY_ERROR\0"
    "DIGEST_ERR\0"
    "ERROR_IN_NEXTUPDATE_FIELD\0"
    "ERROR_IN_THISUPDATE_FIELD\0"
    "ERROR_PARSING_URL\0"
    "MISSING_OCSPSIGNING_USAGE\0"
    "NEXTUPDATE_BEFORE_THISUPDATE\0"
    "NOT_BASIC_RESPONSE\0"
    "NO_CERTIFICATES_IN_CHAIN\0"
    "NO_RESPONSE_DATA\0"
    "NO_SIGNER_KEY\0"
    "OCSP_REQUEST_DUPLICATE_SIGNATURE\0"
    "PRIVATE_KEY_DOES_NOT_MATCH_CERTIFICATE\0"
    "RESPONSE_CONTAINS_NO_REVOCATION_DATA\0"
    "ROOT_CA_NOT_TRUSTED\0"
    "SERVER_RESPONSE_PARSE_ERROR\0"
    "SIGNATURE_FAILURE\0"
    "SIGNER_CERTIFICATE_NOT_FOUND\0"
    "STATUS_EXPIRED\0"
    "STATUS_NOT_YET_VALID\0"
    "STATUS_TOO_OLD\0"
    "UNKNOWN_MESSAGE_DIGEST\0"
    "BAD_BASE64_DECODE\0"
    "BAD_END_LINE\0"
    "BAD_IV_CHARS\0"
    "BAD_PASSWORD_READ\0"
    "CIPHER_IS_NULL\0"
    "ERROR_CONVERTING_PRIVATE_KEY\0"
    "NOT_DEK_INFO\0"
    "NOT_ENCRYPTED\0"
    "NOT_PROC_TYPE\0"
    "NO_START_LINE\0"
    "PROBLEMS_GETTING_PASSWORD\0"
    "READ_KEY\0"
    "SHORT_HEADER\0"
    "UNSUPPORTED_CIPHER\0"
    "UNSUPPORTED_ENCRYPTION\0"
    "BAD_PKCS7_VERSION\0"
    "NOT_PKCS7_SIGNED_DATA\0"
    "NO_CERTIFICATES_INCLUDED\0"
    "NO_CRLS_INCLUDED\0"
    "AMBIGUOUS_FRIENDLY_NAME\0"
    "BAD_ITERATION_COUNT\0"
    "BAD_PKCS12_DATA\0"
    "BAD_PKCS12_VERSION\0"
    "CIPHER_HAS_NO_OBJECT_IDENTIFIER\0"
    "CRYPT_ERROR\0"
    "ENCRYPT_ERROR\0"
    "ERROR_SETTING_CIPHER_PARAMS\0"
    "INCORRECT_PASSWORD\0"
    "INVALID_CHARACTERS\0"
    "KEYGEN_FAILURE\0"
    "KEY_GEN_ERROR\0"
    "METHOD_NOT_SUPPORTED\0"
    "MISSING_MAC\0"
    "MULTIPLE_PRIVATE_KEYS_IN_PKCS12\0"
    "PKCS12_PUBLIC_KEY_INTEGRITY_NOT_SUPPORTED\0"
    "PKCS12_TOO_DEEPLY_NESTED\0"
    "PRIVATE_KEY_DECODE_ERROR\0"
    "PRIVATE_KEY_ENCODE_ERROR\0"
    "UNKNOWN_ALGORITHM\0"
    "UNKNOWN_CIPHER\0"
    "UNKNOWN_CIPHER_ALGORITHM\0"
    "UNKNOWN_DIGEST\0"
    "UNSUPPORTED_KEYLENGTH\0"
    "UNSUPPORTED_KEY_DERIVATION_FUNCTION\0"
    "UNSUPPORTED_OPTIONS\0"
    "UNSUPPORTED_PRF\0"
    "UNSUPPORTED_PRIVATE_KEY_ALGORITHM\0"
    "UNSUPPORTED_SALT_TYPE\0"
    "BAD_E_VALUE\0"
    "BAD_FIXED_HEADER_DECRYPT\0"
    "BAD_PAD_BYTE_COUNT\0"
    "BAD_RSA_PARAMETERS\0"
    "BLOCK_TYPE_IS_NOT_01\0"
    "BLOCK_TYPE_IS_NOT_02\0"
    "BN_NOT_INITIALIZED\0"
    "CANNOT_RECOVER_MULTI_PRIME_KEY\0"
    "CRT_PARAMS_ALREADY_GIVEN\0"
    "CRT_VALUES_INCORRECT\0"
    "DATA_LEN_NOT_EQUAL_TO_MOD_LEN\0"
    "DATA_TOO_LARGE\0"
    "DATA_TOO_LARGE_FOR_KEY_SIZE\0"
    "DATA_TOO_LARGE_FOR_MODULUS\0"
    "DATA_TOO_SMALL\0"
    "DATA_TOO_SMALL_FOR_KEY_SIZE\0"
    "DIGEST_TOO_BIG_FOR_RSA_KEY\0"
    "D_E_NOT_CONGRUENT_TO_1\0"
    "D_OUT_OF_RANGE\0"
    "EMPTY_PUBLIC_KEY\0"
    "FIRST_OCTET_INVALID\0"
    "INCONSISTENT_SET_OF_CRT_VALUES\0"
    "INTERNAL_ERROR\0"
    "INVALID_MESSAGE_LENGTH\0"
    "KEY_SIZE_TOO_SMALL\0"
    "LAST_OCTET_INVALID\0"
    "MUST_HAVE_AT_LEAST_TWO_PRIMES\0"
    "NO_PUBLIC_EXPONENT\0"
    "NULL_BEFORE_BLOCK_MISSING\0"
    "N_NOT_EQUAL_P_Q\0"
    "OAEP_DECODING_ERROR\0"
    "ONLY_ONE_OF_P_Q_GIVEN\0"
    "OUTPUT_BUFFER_TOO_SMALL\0"
    "PADDING_CHECK_FAILED\0"
    "PKCS_DECODING_ERROR\0"
    "SLEN_CHECK_FAILED\0"
    "SLEN_RECOVERY_FAILED\0"
    "UNKNOWN_ALGORITHM_TYPE\0"
    "UNKNOWN_PADDING_TYPE\0"
    "VALUE_MISSING\0"
    "WRONG_SIGNATURE_LENGTH\0"
    "ALPN_MISMATCH_ON_EARLY_DATA\0"
    "ALPS_MISMATCH_ON_EARLY_DATA\0"
    "APPLICATION_DATA_INSTEAD_OF_HANDSHAKE\0"
    "APPLICATION_DATA_ON_SHUTDOWN\0"
    "APP_DATA_IN_HANDSHAKE\0"
    "ATTEMPT_TO_REUSE_SESSION_IN_DIFFERENT_CONTEXT\0"
    "BAD_ALERT\0"
    "BAD_CHANGE_CIPHER_SPEC\0"
    "BAD_DATA_RETURNED_BY_CALLBACK\0"
    "BAD_DH_P_LENGTH\0"
    "BAD_DIGEST_LENGTH\0"
    "BAD_ECC_CERT\0"
    "BAD_ECPOINT\0"
    "BAD_HANDSHAKE_RECORD\0"
    "BAD_HELLO_REQUEST\0"
    "BAD_LENGTH\0"
    "BAD_PACKET_LENGTH\0"
    "BAD_RSA_ENCRYPT\0"
    "BAD_SRTP_MKI_VALUE\0"
    "BAD_SRTP_PROTECTION_PROFILE_LIST\0"
    "BAD_SSL_FILETYPE\0"
    "BAD_WRITE_RETRY\0"
    "BIO_NOT_SET\0"
    "BLOCK_CIPHER_PAD_IS_WRONG\0"
    "CANNOT_HAVE_BOTH_PRIVKEY_AND_METHOD\0"
    "CANNOT_PARSE_LEAF_CERT\0"
    "CA_DN_LENGTH_MISMATCH\0"
    "CA_DN_TOO_LONG\0"
    "CCS_RECEIVED_EARLY\0"
    "CERTIFICATE_AND_PRIVATE_KEY_MISMATCH\0"
    "CERTIFICATE_VERIFY_FAILED\0"
    "CERT_CB_ERROR\0"
    "CERT_DECOMPRESSION_FAILED\0"
    "CERT_LENGTH_MISMATCH\0"
    "CHANNEL_ID_NOT_P256\0"
    "CHANNEL_ID_SIGNATURE_INVALID\0"
    "CIPHER_MISMATCH_ON_EARLY_DATA\0"
    "CIPHER_OR_HASH_UNAVAILABLE\0"
    "CLIENTHELLO_PARSE_FAILED\0"
    "CLIENTHELLO_TLSEXT\0"
    "CONNECTION_REJECTED\0"
    "CONNECTION_TYPE_NOT_SET\0"
    "COULD_NOT_PARSE_HINTS\0"
    "CUSTOM_EXTENSION_ERROR\0"
    "DATA_LENGTH_TOO_LONG\0"
    "DECRYPTION_FAILED\0"
    "DECRYPTION_FAILED_OR_BAD_RECORD_MAC\0"
    "DH_PUBLIC_VALUE_LENGTH_IS_WRONG\0"
    "DH_P_TOO_LONG\0"
    "DIGEST_CHECK_FAILED\0"
    "DOWNGRADE_DETECTED\0"
    "DTLS_MESSAGE_TOO_BIG\0"
    "DUPLICATE_EXTENSION\0"
    "DUPLICATE_KEY_SHARE\0"
    "DUPLICATE_SIGNATURE_ALGORITHM\0"
    "EARLY_DATA_NOT_IN_USE\0"
    "ECC_CERT_NOT_FOR_SIGNING\0"
    "ECH_REJECTED\0"
    "ECH_SERVER_CONFIG_AND_PRIVATE_KEY_MISMATCH\0"
    "ECH_SERVER_CONFIG_UNSUPPORTED_EXTENSION\0"
    "ECH_SERVER_WOULD_HAVE_NO_RETRY_CONFIGS\0"
    "EMPTY_HELLO_RETRY_REQUEST\0"
    "EMS_STATE_INCONSISTENT\0"
    "ENCRYPTED_LENGTH_TOO_LONG\0"
    "ERROR_ADDING_EXTENSION\0"
    "ERROR_IN_RECEIVED_CIPHER_LIST\0"
    "ERROR_PARSING_EXTENSION\0"
    "EXCESSIVE_MESSAGE_SIZE\0"
    "EXCESS_HANDSHAKE_DATA\0"
    "EXTRA_DATA_IN_MESSAGE\0"
    "FRAGMENT_MISMATCH\0"
    "GOT_NEXT_PROTO_WITHOUT_EXTENSION\0"
    "HANDSHAKE_FAILURE_ON_CLIENT_HELLO\0"
    "HANDSHAKE_NOT_COMPLETE\0"
    "HTTPS_PROXY_REQUEST\0"
    "HTTP_REQUEST\0"
    "INAPPROPRIATE_FALLBACK\0"
    "INCONSISTENT_CLIENT_HELLO\0"
    "INCONSISTENT_ECH_NEGOTIATION\0"
    "INVALID_ALPN_PROTOCOL\0"
    "INVALID_ALPN_PROTOCOL_LIST\0"
    "INVALID_CLIENT_HELLO_INNER\0"
    "INVALID_COMMAND\0"
    "INVALID_COMPRESSION_LIST\0"
    "INVALID_DELEGATED_CREDENTIAL\0"
    "INVALID_ECH_CONFIG_LIST\0"
    "INVALID_ECH_PUBLIC_NAME\0"
    "INVALID_MESSAGE\0"
    "INVALID_OUTER_EXTENSION\0"
    "INVALID_OUTER_RECORD_TYPE\0"
    "INVALID_SCT_LIST\0"
    "INVALID_SIGNATURE_ALGORITHM\0"
    "INVALID_SSL_SESSION\0"
    "INVALID_TICKET_KEYS_LENGTH\0"
    "KEY_USAGE_BIT_INCORRECT\0"
    "LENGTH_MISMATCH\0"
    "MISSING_EXTENSION\0"
    "MISSING_KEY_SHARE\0"
    "MISSING_RSA_CERTIFICATE\0"
    "MISSING_TMP_DH_KEY\0"
    "MISSING_TMP_ECDH_KEY\0"
    "MIXED_SPECIAL_OPERATOR_WITH_GROUPS\0"
    "MTU_TOO_SMALL\0"
    "NEGOTIATED_ALPS_WITHOUT_ALPN\0"
    "NEGOTIATED_BOTH_NPN_AND_ALPN\0"
    "NEGOTIATED_TB_WITHOUT_EMS_OR_RI\0"
    "NESTED_GROUP\0"
    "NO_APPLICATION_PROTOCOL\0"
    "NO_CERTIFICATES_RETURNED\0"
    "NO_CERTIFICATE_ASSIGNED\0"
    "NO_CERTIFICATE_SET\0"
    "NO_CIPHERS_AVAILABLE\0"
    "NO_CIPHERS_PASSED\0"
    "NO_CIPHERS_SPECIFIED\0"
    "NO_CIPHER_MATCH\0"
    "NO_COMMON_SIGNATURE_ALGORITHMS\0"
    "NO_COMPRESSION_SPECIFIED\0"
    "NO_GROUPS_SPECIFIED\0"
    "NO_METHOD_SPECIFIED\0"
    "NO_P256_SUPPORT\0"
    "NO_PRIVATE_KEY_ASSIGNED\0"
    "NO_RENEGOTIATION\0"
    "NO_REQUIRED_DIGEST\0"
    "NO_SHARED_CIPHER\0"
    "NO_SHARED_GROUP\0"
    "NO_SUPPORTED_VERSIONS_ENABLED\0"
    "NULL_SSL_CTX\0"
    "NULL_SSL_METHOD_PASSED\0"
    "OCSP_CB_ERROR\0"
    "OLD_SESSION_CIPHER_NOT_RETURNED\0"
    "OLD_SESSION_PRF_HASH_MISMATCH\0"
    "OLD_SESSION_VERSION_NOT_RETURNED\0"
    "PARSE_TLSEXT\0"
    "PATH_TOO_LONG\0"
    "PEER_DID_NOT_RETURN_A_CERTIFICATE\0"
    "PEER_ERROR_UNSUPPORTED_CERTIFICATE_TYPE\0"
    "PRE_SHARED_KEY_MUST_BE_LAST\0"
    "PRIVATE_KEY_OPERATION_FAILED\0"
    "PROTOCOL_IS_SHUTDOWN\0"
    "PSK_IDENTITY_BINDER_COUNT_MISMATCH\0"
    "PSK_IDENTITY_NOT_FOUND\0"
    "PSK_NO_CLIENT_CB\0"
    "PSK_NO_SERVER_CB\0"
    "QUIC_INTERNAL_ERROR\0"
    "QUIC_TRANSPORT_PARAMETERS_MISCONFIGURED\0"
    "READ_TIMEOUT_EXPIRED\0"
    "RECORD_LENGTH_MISMATCH\0"
    "RECORD_TOO_LARGE\0"
    "RENEGOTIATION_EMS_MISMATCH\0"
    "RENEGOTIATION_ENCODING_ERR\0"
    "RENEGOTIATION_MISMATCH\0"
    "REQUIRED_CIPHER_MISSING\0"
    "RESUMED_EMS_SESSION_WITHOUT_EMS_EXTENSION\0"
    "RESUMED_NON_EMS_SESSION_WITH_EMS_EXTENSION\0"
    "SCSV_RECEIVED_WHEN_RENEGOTIATING\0"
    "SECOND_SERVERHELLO_VERSION_MISMATCH\0"
    "SERIALIZATION_INVALID_SSL\0"
    "SERIALIZATION_INVALID_SSL3_STATE\0"
    "SERIALIZATION_INVALID_SSL_AEAD_CONTEXT\0"
    "SERIALIZATION_INVALID_SSL_BUFFER\0"
    "SERIALIZATION_INVALID_SSL_CONFIG\0"
    "SERIALIZATION_UNSUPPORTED\0"
    "SERVERHELLO_TLSEXT\0"
    "SERVER_CERT_CHANGED\0"
    "SERVER_ECHOED_INVALID_SESSION_ID\0"
    "SESSION_ID_CONTEXT_UNINITIALIZED\0"
    "SESSION_MAY_NOT_BE_CREATED\0"
    "SHUTDOWN_WHILE_IN_INIT\0"
    "SIGNATURE_ALGORITHMS_EXTENSION_SENT_BY_SERVER\0"
    "SRTP_COULD_NOT_ALLOCATE_PROFILES\0"
    "SRTP_UNKNOWN_PROTECTION_PROFILE\0"
    "SSL3_EXT_INVALID_SERVERNAME\0"
    "SSLV3_ALERT_BAD_CERTIFICATE\0"
    "SSLV3_ALERT_BAD_RECORD_MAC\0"
    "SSLV3_ALERT_CERTIFICATE_EXPIRED\0"
    "SSLV3_ALERT_CERTIFICATE_REVOKED\0"
    "SSLV3_ALERT_CERTIFICATE_UNKNOWN\0"
    "SSLV3_ALERT_CLOSE_NOTIFY\0"
    "SSLV3_ALERT_DECOMPRESSION_FAILURE\0"
    "SSLV3_ALERT_HANDSHAKE_FAILURE\0"
    "SSLV3_ALERT_ILLEGAL_PARAMETER\0"
    "SSLV3_ALERT_NO_CERTIFICATE\0"
    "SSLV3_ALERT_UNEXPECTED_MESSAGE\0"
    "SSLV3_ALERT_UNSUPPORTED_CERTIFICATE\0"
    "SSL_CTX_HAS_NO_DEFAULT_SSL_VERSION\0"
    "SSL_HANDSHAKE_FAILURE\0"
    "SSL_SESSION_ID_CONTEXT_TOO_LONG\0"
    "SSL_SESSION_ID_TOO_LONG\0"
    "TICKET_ENCRYPTION_FAILED\0"
    "TLS13_DOWNGRADE\0"
    "TLSV1_ALERT_ACCESS_DENIED\0"
    "TLSV1_ALERT_BAD_CERTIFICATE_HASH_VALUE\0"
    "TLSV1_ALERT_BAD_CERTIFICATE_STATUS_RESPONSE\0"
    "TLSV1_ALERT_CERTIFICATE_REQUIRED\0"
    "TLSV1_ALERT_CERTIFICATE_UNOBTAINABLE\0"
    "TLSV1_ALERT_DECODE_ERROR\0"
    "TLSV1_ALERT_DECRYPTION_FAILED\0"
    "TLSV1_ALERT_DECRYPT_ERROR\0"
    "TLSV1_ALERT_ECH_REQUIRED\0"
    "TLSV1_ALERT_EXPORT_RESTRICTION\0"
    "TLSV1_ALERT_INAPPROPRIATE_FALLBACK\0"
    "TLSV1_ALERT_INSUFFICIENT_SECURITY\0"
    "TLSV1_ALERT_INTERNAL_ERROR\0"
    "TLSV1_ALERT_NO_APPLICATION_PROTOCOL\0"
    "TLSV1_ALERT_NO_RENEGOTIATION\0"
    "TLSV1_ALERT_PROTOCOL_VERSION\0"
    "TLSV1_ALERT_RECORD_OVERFLOW\0"
    "TLSV1_ALERT_UNKNOWN_CA\0"
    "TLSV1_ALERT_UNKNOWN_PSK_IDENTITY\0"
    "TLSV1_ALERT_UNRECOGNIZED_NAME\0"
    "TLSV1_ALERT_UNSUPPORTED_EXTENSION\0"
    "TLSV1_ALERT_USER_CANCELLED\0"
    "TLS_PEER_DID_NOT_RESPOND_WITH_CERTIFICATE_LIST\0"
    "TLS_RSA_ENCRYPTED_VALUE_LENGTH_IS_WRONG\0"
    "TOO_MANY_EMPTY_FRAGMENTS\0"
    "TOO_MANY_KEY_UPDATES\0"
    "TOO_MANY_WARNING_ALERTS\0"
    "TOO_MUCH_READ_EARLY_DATA\0"
    "TOO_MUCH_SKIPPED_EARLY_DATA\0"
    "UNABLE_TO_FIND_ECDH_PARAMETERS\0"
    "UNCOMPRESSED_CERT_TOO_LARGE\0"
    "UNEXPECTED_COMPATIBILITY_MODE\0"
    "UNEXPECTED_EXTENSION\0"
    "UNEXPECTED_EXTENSION_ON_EARLY_DATA\0"
    "UNEXPECTED_MESSAGE\0"
    "UNEXPECTED_OPERATOR_IN_GROUP\0"
    "UNEXPECTED_RECORD\0"
    "UNKNOWN_ALERT_TYPE\0"
    "UNKNOWN_CERTIFICATE_TYPE\0"
    "UNKNOWN_CERT_COMPRESSION_ALG\0"
    "UNKNOWN_CIPHER_RETURNED\0"
    "UNKNOWN_CIPHER_TYPE\0"
    "UNKNOWN_KEY_EXCHANGE_TYPE\0"
    "UNKNOWN_PROTOCOL\0"
    "UNKNOWN_SSL_VERSION\0"
    "UNKNOWN_STATE\0"
    "UNSAFE_LEGACY_RENEGOTIATION_DISABLED\0"
    "UNSUPPORTED_COMPRESSION_ALGORITHM\0"
    "UNSUPPORTED_ECH_SERVER_CONFIG\0"
    "UNSUPPORTED_ELLIPTIC_CURVE\0"
    "UNSUPPORTED_PROTOCOL\0"
    "UNSUPPORTED_PROTOCOL_FOR_CUSTOM_KEY\0"
    "WRONG_CERTIFICATE_TYPE\0"
    "WRONG_CIPHER_RETURNED\0"
    "WRONG_CURVE\0"
    "WRONG_ENCRYPTION_LEVEL_RECEIVED\0"
    "WRONG_MESSAGE_TYPE\0"
    "WRONG_SIGNATURE_TYPE\0"
    "WRONG_SSL_VERSION\0"
    "WRONG_VERSION_NUMBER\0"
    "WRONG_VERSION_ON_EARLY_DATA\0"
    "X509_LIB\0"
    "X509_VERIFICATION_SETUP_PROBLEMS\0"
    "BAD_VALIDITY_CHECK\0"
    "DECODE_FAILURE\0"
    "INVALID_KEY_ID\0"
    "INVALID_METADATA\0"
    "INVALID_METADATA_KEY\0"
    "INVALID_PROOF\0"
    "INVALID_TOKEN\0"
    "NO_KEYS_CONFIGURED\0"
    "NO_SRR_KEY_CONFIGURED\0"
    "OVER_BATCHSIZE\0"
    "SRR_SIGNATURE_ERROR\0"
    "TOO_MANY_KEYS\0"
    "AKID_MISMATCH\0"
    "BAD_X509_FILETYPE\0"
    "BASE64_DECODE_ERROR\0"
    "CANT_CHECK_DH_KEY\0"
    "CERT_ALREADY_IN_HASH_TABLE\0"
    "CRL_ALREADY_DELTA\0"
    "CRL_VERIFY_FAILURE\0"
    "DELTA_CRL_WITHOUT_CRL_NUMBER\0"
    "IDP_MISMATCH\0"
    "INVALID_DIRECTORY\0"
    "INVALID_FIELD_FOR_VERSION\0"
    "INVALID_FIELD_NAME\0"
    "INVALID_PARAMETER\0"
    "INVALID_POLICY_EXTENSION\0"
    "INVALID_PSS_PARAMETERS\0"
    "INVALID_TRUST\0"
    "INVALID_VERSION\0"
    "ISSUER_MISMATCH\0"
    "KEY_TYPE_MISMATCH\0"
    "KEY_VALUES_MISMATCH\0"
    "LOADING_CERT_DIR\0"
    "LOADING_DEFAULTS\0"
    "NAME_TOO_LONG\0"
    "NEWER_CRL_NOT_NEWER\0"
    "NO_CERTIFICATE_FOUND\0"
    "NO_CERTIFICATE_OR_CRL_FOUND\0"
    "NO_CERT_SET_FOR_US_TO_VERIFY\0"
    "NO_CRL_FOUND\0"
    "NO_CRL_NUMBER\0"
    "PUBLIC_KEY_DECODE_ERROR\0"
    "PUBLIC_KEY_ENCODE_ERROR\0"
    "SHOULD_RETRY\0"
    "SIGNATURE_ALGORITHM_MISMATCH\0"
    "UNKNOWN_KEY_TYPE\0"
    "UNKNOWN_PURPOSE_ID\0"
    "UNKNOWN_TRUST_ID\0"
    "WRONG_LOOKUP_TYPE\0"
    "BAD_IP_ADDRESS\0"
    "BAD_OBJECT\0"
    "BN_DEC2BN_ERROR\0"
    "BN_TO_ASN1_INTEGER_ERROR\0"
    "CANNOT_FIND_FREE_FUNCTION\0"
    "DIRNAME_ERROR\0"
    "DISTPOINT_ALREADY_SET\0"
    "DUPLICATE_ZONE_ID\0"
    "ERROR_CONVERTING_ZONE\0"
    "ERROR_CREATING_EXTENSION\0"
    "ERROR_IN_EXTENSION\0"
    "EXPECTED_A_SECTION_NAME\0"
    "EXTENSION_EXISTS\0"
    "EXTENSION_NAME_ERROR\0"
    "EXTENSION_NOT_FOUND\0"
    "EXTENSION_SETTING_NOT_SUPPORTED\0"
    "EXTENSION_VALUE_ERROR\0"
    "ILLEGAL_EMPTY_EXTENSION\0"
    "ILLEGAL_HEX_DIGIT\0"
    "INCORRECT_POLICY_SYNTAX_TAG\0"
    "INVALID_BOOLEAN_STRING\0"
    "INVALID_EXTENSION_STRING\0"
    "INVALID_MULTIPLE_RDNS\0"
    "INVALID_NAME\0"
    "INVALID_NULL_ARGUMENT\0"
    "INVALID_NULL_NAME\0"
    "INVALID_NULL_VALUE\0"
    "INVALID_NUMBERS\0"
    "INVALID_OBJECT_IDENTIFIER\0"
    "INVALID_OPTION\0"
    "INVALID_POLICY_IDENTIFIER\0"
    "INVALID_PROXY_POLICY_SETTING\0"
    "INVALID_PURPOSE\0"
    "INVALID_SECTION\0"
    "INVALID_SYNTAX\0"
    "INVALID_VALUE\0"
    "ISSUER_DECODE_ERROR\0"
    "NEED_ORGANIZATION_AND_NUMBERS\0"
    "NO_CONFIG_DATABASE\0"
    "NO_ISSUER_CERTIFICATE\0"
    "NO_ISSUER_DETAILS\0"
    "NO_POLICY_IDENTIFIER\0"
    "NO_PROXY_CERT_POLICY_LANGUAGE_DEFINED\0"
    "NO_PUBLIC_KEY\0"
    "NO_SUBJECT_DETAILS\0"
    "ODD_NUMBER_OF_DIGITS\0"
    "OPERATION_NOT_DEFINED\0"
    "OTHERNAME_ERROR\0"
    "POLICY_LANGUAGE_ALREADY_DEFINED\0"
    "POLICY_PATH_LENGTH\0"
    "POLICY_PATH_LENGTH_ALREADY_DEFINED\0"
    "POLICY_WHEN_PROXY_LANGUAGE_REQUIRES_NO_POLICY\0"
    "SECTION_NOT_FOUND\0"
    "TRAILING_DATA_IN_EXTENSION\0"
    "UNABLE_TO_GET_ISSUER_DETAILS\0"
    "UNABLE_TO_GET_ISSUER_KEYID\0"
    "UNKNOWN_BIT_STRING_ARGUMENT\0"
    "UNKNOWN_EXTENSION\0"
    "UNKNOWN_EXTENSION_NAME\0"
    "UNKNOWN_OPTION\0"
    "UNSUPPORTED_OPTION\0"
    "USER_TOO_LONG\0"
    "";

