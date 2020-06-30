
/* Apache License 2.0 */

/*
	�ļ���yd_aes_ecb.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺AES�㷨ģʽECB(Electronic Codebook)ʵ�֣�����ο���SP800-38A��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#ifndef YD_AES_ECB_H
#define YD_AES_ECB_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_aes_ecb_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint32_t blk);
void yd_aes_ecb_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_AES_ECB_H */
