
/* ��ѣ������ */

/*
	�ļ���yd_aes_base.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺AES�㷨���ģ�����ο���FIPS PUB 197��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#ifndef YD_AES_BASE_H
#define YD_AES_BASE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


#define AES_ENCRYPT					0
#define AES_DECRYPT					1

#define AES_NK						4 //4����(16�ֽ�).
//#define AES_NK					6 //6����(24�ֽ�).
//#define AES_NK					8 //8����(32�ֽ�).

#if AES_NK == 4
	#define AES_NR					10 //��������.
#elif AES_NK == 6
	#define AES_NR					12
#elif AES_NK == 8
	#define AES_NR					14
#else
	#error	AES must be 128 192 256bit!
#endif


void yd_aes_encrypt(uint8_t *state, uint8_t *key);
void yd_aes_decrypt(uint8_t *state, uint8_t *key);

#ifdef __cplusplus
}
#endif

#endif /* YD_AES_BASE_H */
