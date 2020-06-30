
/* Apache License 2.0 */

/*
	文件：yd_aes_ecb.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：AES算法模式ECB(Electronic Codebook)实现，详情参考《SP800-38A》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
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
