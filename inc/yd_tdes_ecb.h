
/* ��ѣ������ */

/*
	�ļ���yd_tdes_ecb.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺TDES�㷨ģʽECB(Electronic Codebook)ʵ�֣�����ο���ANSI X9.52-1998��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#ifndef YD_TDES_ECB_H
#define YD_TDES_ECB_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_tdes_ecb_encrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint32_t blk);
void yd_tdes_ecb_decrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_TDES_ECB_H */
