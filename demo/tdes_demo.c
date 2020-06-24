
#include "demo.h"
#include "yd_tdes_ecb.h"
#include "yd_tdes_cbc.h"
#include "yd_tdes_cfb.h"
#include "yd_tdes_ofb.h"


static uint8_t k1[]={0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
static uint8_t k2[]={0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01};
static uint8_t k3[]={0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23};
static uint8_t iv[8]={0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
static uint8_t str[]="Now is the time for all ";


/* TECB模式 */
void tdes_ecb_demo(void)
{
	uint8_t enc[24], dec[24];
	
	yd_tdes_ecb_encrypt(str, enc, k1, k2, k3, 3);
	yd_tdes_ecb_decrypt(enc, dec, k1, k2, k3, 3);
}

/* TCBC模式 */
void tdes_cbc_demo(void)
{
	uint8_t enc[24], dec[24];
	
	yd_tdes_cbc_encrypt(str, enc, k1, k2, k3, iv, 3);
	yd_tdes_cbc_decrypt(enc, dec, k1, k2, k3, iv, 3);
}

/* TCFB8模式 */
void tdes_cfb8_demo(void)
{
	uint8_t enc[10], dec[10];
	
	yd_tdes_cfb8_encrypt(str, enc, k1, k2, k3, iv, 10);
	yd_tdes_cfb8_decrypt(enc, dec, k1, k2, k3, iv, 10);
}

/* TCFB64模式 */
void tdes_cfb64_demo(void)
{
	uint8_t enc[24], dec[24];
	
	yd_tdes_cfb64_encrypt(str, enc, k1, k2, k3, iv, 3);
	yd_tdes_cfb64_decrypt(enc, dec, k1, k2, k3, iv, 3);
}

/* TOFB模式 */
void tdes_ofb_demo(void)
{
	uint8_t enc[24], dec[24];
	
	yd_tdes_ofb_enc_dec_crypto(str, enc, k1, k2, k3, iv, 3);
	yd_tdes_ofb_enc_dec_crypto(enc, dec, k1, k2, k3, iv, 3);
}
