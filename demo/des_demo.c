
#include "demo.h"
#include "yd_des_ecb.h"
#include "yd_des_cbc.h"
#include "yd_des_cfb.h"
#include "yd_des_ofb.h"


/* ECB、CBC模式 */
void des_ecb_cbc_demo(void)
{
	uint8_t iv[8]={0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
	uint8_t key[8]={0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
	uint8_t str[]="Now is the time for all ";
	uint8_t dec[24], enc[24];
	
	yd_des_ecb_encrypt(str, enc, key, 3);
	yd_des_ecb_decrypt(enc, dec, key, 3);
	
	yd_des_cbc_encrypt(str, enc, key, iv, 3);
	yd_des_cbc_decrypt(enc, dec, key, iv, 3);
}

/* CFB模式 */
void des_cfb_demo(void)
{
	uint8_t iv[8]={0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
	uint8_t key[8]={0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
	uint8_t str8[]="Now is the";
	uint8_t dec8[10], enc8[10];
	uint8_t str64[]="Now is the time for all ";
	uint8_t dec64[24], enc64[24];
	
	yd_des_cfb8_encrypt(str8, enc8, key, iv, 10);
	yd_des_cfb8_decrypt(enc8, dec8, key, iv, 10);
	
	yd_des_cfb64_encrypt(str64, enc64, key, iv, 3);
	yd_des_cfb64_decrypt(enc64, dec64, key, iv, 3);
}

/* OFB模式 */
void des_ofb_demo(void)
{
	uint8_t iv[8]={0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
	uint8_t key[8]={0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
	uint8_t str8[]="Now is the";
	uint8_t dec8[10], enc8[10];
	uint8_t str64[]="Now is the time for all ";
	uint8_t dec64[24], enc64[24];
	
	yd_des_ofb8_enc_dec_crypto(str8, enc8, key, iv, 10); //加密.
	yd_des_ofb8_enc_dec_crypto(enc8, dec8, key, iv, 10); //解密.
	
	yd_des_ofb64_enc_dec_crypto(str64, enc64, key, iv, 3); //加密.
	yd_des_ofb64_enc_dec_crypto(enc64, dec64, key, iv, 3); //解密.
}
