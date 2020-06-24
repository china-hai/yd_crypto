
/* ��ѣ������ */

/*
	�ļ���yd_aes_cfb.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺AES�㷨ģʽCFB(Cipher Feedback)ʵ�֣�����ο���SP800-38A��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#ifndef YD_AES_CFB_H
#define YD_AES_CFB_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_aes_cfb8_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t num);
void yd_aes_cfb8_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t num);

void yd_aes_cfb128_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);
void yd_aes_cfb128_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_AES_CFB_H */
