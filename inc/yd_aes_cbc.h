
/* 免费，无许可 */

/*
	文件：yd_aes_cbc.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：AES算法模式CBC(Cipher Block Chaining)实现，详情参考《SP800-38A》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#ifndef YD_AES_CBC_H
#define YD_AES_CBC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_aes_cbc_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);
void yd_aes_cbc_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_AES_CBC_H */
