
#include "demo.h"
#include "yd_aes_base.h"
#include "yd_aes_ecb.h"
#include "yd_aes_cbc.h"
#include "yd_aes_cfb.h"
#include "yd_aes_ofb.h"
#include "yd_aes_cbc_cs.h"


static uint8_t str[64]={0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
						0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
						0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,
						0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
						0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11,
						0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
						0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17,
						0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10};

#if	AES_NK == 4
static uint8_t key4[16]={0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
						 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

#elif AES_NK == 6
static uint8_t key6[24]={0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52,
						 0xc8, 0x10, 0xf3, 0x2b, 0x80, 0x90, 0x79, 0xe5,
						 0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b};
#else
static uint8_t key8[32]={0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
						 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
						 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7,
						 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4};
#endif

static uint8_t iv[16]= {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
						0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};


/* ECB模式 */
void aes_ecb_demo(void)
{
	uint8_t enc[64], dec[64];
	
#if	AES_NK == 4
	/* yd_aes_base.h中定义AES_NK=4 */
	yd_aes_ecb_encrypt(str, enc, key4, 4);
	yd_aes_ecb_decrypt(enc, dec, key4, 4);
#elif AES_NK == 6
	/* yd_aes_base.h中定义AES_NK=6 */
	yd_aes_ecb_encrypt(str, enc, key6, 4);
	yd_aes_ecb_decrypt(enc, dec, key6, 4);
#else
	/* yd_aes_base.h中定义AES_NK=8 */
	yd_aes_ecb_encrypt(str, enc, key8, 4);
	yd_aes_ecb_decrypt(enc, dec, key8, 4);
#endif
}

/* CBC模式 */
void aes_cbc_demo(void)
{
	uint8_t enc[64], dec[64];
	
#if	AES_NK == 4
	/* yd_aes_base.h中定义AES_NK=4 */
	yd_aes_cbc_encrypt(str, enc, key4, iv, 4);
	yd_aes_cbc_decrypt(enc, dec, key4, iv, 4);
#elif AES_NK == 6
	/* yd_aes_base.h中定义AES_NK=6 */
	yd_aes_cbc_encrypt(str, enc, key6, iv, 4);
	yd_aes_cbc_decrypt(enc, dec, key6, iv, 4);
#else
	/* yd_aes_base.h中定义AES_NK=8 */	
	yd_aes_cbc_encrypt(str, enc, key8, iv, 4);
	yd_aes_cbc_decrypt(enc, dec, key8, iv, 4);
#endif
}

/* CFB模式 */
void aes_cfb_demo(void)
{
	uint8_t enc8[18], dec8[18];
	uint8_t enc128[64], dec128[64];
	
#if	AES_NK == 4
	/* yd_aes_base.h中定义AES_NK=4 */
	yd_aes_cfb8_encrypt(str, enc8, key4, iv, 18);
	yd_aes_cfb8_decrypt(enc8, dec8, key4, iv, 18);
	
	yd_aes_cfb128_encrypt(str, enc128, key4, iv, 4);
	yd_aes_cfb128_decrypt(enc128, dec128, key4, iv, 4);
#elif AES_NK == 6
	/* yd_aes_base.h中定义AES_NK=6 */
	yd_aes_cfb8_encrypt(str, enc8, key6, iv, 18);
	yd_aes_cfb8_decrypt(enc8, dec8, key6, iv, 18);
	
	yd_aes_cfb128_encrypt(str, enc128, key6, iv, 4);
	yd_aes_cfb128_decrypt(enc128, dec128, key6, iv, 4);
#else
	/* yd_aes_base.h中定义AES_NK=8 */
	yd_aes_cfb8_encrypt(str, enc8, key8, iv, 18);
	yd_aes_cfb8_decrypt(enc8, dec8, key8, iv, 18);
	
	yd_aes_cfb128_encrypt(str, enc128, key8, iv, 4);
	yd_aes_cfb128_decrypt(enc128, dec128, key8, iv, 4);
#endif
}

/* OFB模式 */
void aes_ofb_demo(void)
{
	uint8_t enc[64], dec[64];
	
#if	AES_NK == 4
	/* yd_aes_base.h中定义AES_NK=4 */
	yd_aes_ofb_enc_dec_crypto(str, enc, key4, iv, 4);
	yd_aes_ofb_enc_dec_crypto(enc, dec, key4, iv, 4);
#elif AES_NK == 6
	/* yd_aes_base.h中定义AES_NK=6 */
	yd_aes_ofb_enc_dec_crypto(str, enc, key6, iv, 4);
	yd_aes_ofb_enc_dec_crypto(enc, dec, key6, iv, 4);
#else
	/* yd_aes_base.h中定义AES_NK=8 */	
	yd_aes_ofb_enc_dec_crypto(str, enc, key8, iv, 4);
	yd_aes_ofb_enc_dec_crypto(enc, dec, key8, iv, 4);
#endif
}

/* CBC-CS1模式 */
void aes_cbc_cs1_demo(void)
{
	uint8_t enc[64], dec[64];
	
#if	AES_NK == 4
	/* yd_aes_base.h中定义AES_NK=4 */
	yd_aes_cbc_cs1_encrypt(str, enc, key4, iv, 42); //可加密不同字节长度.
	yd_aes_cbc_cs1_decrypt(enc, dec, key4, iv, 42);
#elif AES_NK == 6
	/* yd_aes_base.h中定义AES_NK=6 */
	yd_aes_cbc_cs1_encrypt(str, enc, key6, iv, 32);
	yd_aes_cbc_cs1_decrypt(enc, dec, key6, iv, 32);
#else
	/* yd_aes_base.h中定义AES_NK=8 */	
	yd_aes_cbc_cs1_encrypt(str, enc, key8, iv, 26);
	yd_aes_cbc_cs1_decrypt(enc, dec, key8, iv, 26);
#endif
}

/* CBC-CS2模式 */
void aes_cbc_cs2_demo(void)
{
	uint8_t enc[64], dec[64];
	
#if	AES_NK == 4
	/* yd_aes_base.h中定义AES_NK=4 */
	yd_aes_cbc_cs2_encrypt(str, enc, key4, iv, 42); //可加密不同字节长度.
	yd_aes_cbc_cs2_decrypt(enc, dec, key4, iv, 42);
#elif AES_NK == 6
	/* yd_aes_base.h中定义AES_NK=6 */
	yd_aes_cbc_cs2_encrypt(str, enc, key6, iv, 32);
	yd_aes_cbc_cs2_decrypt(enc, dec, key6, iv, 32);
#else
	/* yd_aes_base.h中定义AES_NK=8 */	
	yd_aes_cbc_cs2_encrypt(str, enc, key8, iv, 26);
	yd_aes_cbc_cs2_decrypt(enc, dec, key8, iv, 26);
#endif
}

/* CBC-CS3模式 */
void aes_cbc_cs3_demo(void)
{
	uint8_t enc[64], dec[64];
	
#if	AES_NK == 4
	/* yd_aes_base.h中定义AES_NK=4 */
	yd_aes_cbc_cs3_encrypt(str, enc, key4, iv, 42); //可加密不同字节长度.
	yd_aes_cbc_cs3_decrypt(enc, dec, key4, iv, 42);
#elif AES_NK == 6
	/* yd_aes_base.h中定义AES_NK=6 */
	yd_aes_cbc_cs3_encrypt(str, enc, key6, iv, 32);
	yd_aes_cbc_cs3_decrypt(enc, dec, key6, iv, 32);
#else
	/* yd_aes_base.h中定义AES_NK=8 */	
	yd_aes_cbc_cs3_encrypt(str, enc, key8, iv, 26);
	yd_aes_cbc_cs3_decrypt(enc, dec, key8, iv, 26);
#endif
}
