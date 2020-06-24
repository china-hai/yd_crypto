
#ifndef DEMO_H
#define DEMO_H

#include <stdint.h>


void des_ecb_cbc_demo(void);
void des_cfb_demo(void);
void des_ofb_demo(void);

void tdes_ecb_demo(void);
void tdes_cbc_demo(void);
void tdes_cfb8_demo(void);
void tdes_cfb64_demo(void);
void tdes_ofb_demo(void);

void aes_ecb_demo(void);
void aes_cbc_demo(void);
void aes_cfb_demo(void);
void aes_ofb_demo(void);

void md5_demo(void);

void sha1_demo(void);
void sha224_demo(void);
void sha256_demo(void);

#endif
