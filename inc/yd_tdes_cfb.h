
/* 免费，无许可 */

/*
	文件：yd_tdes_cfb.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：TDES算法模式CFB(Cipher Feedback)实现，详情参考《ANSI X9.52-1998》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#ifndef YD_TDES_CFB_H
#define YD_TDES_CFB_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_tdes_cfb8_encrypt(uint8_t *in,
						  uint8_t *out,
						  uint8_t *key1,
						  uint8_t *key2,
						  uint8_t *key3,
						  uint8_t *iv,
						  uint32_t num);
void yd_tdes_cfb8_decrypt(uint8_t *in,
						  uint8_t *out,
						  uint8_t *key1,
						  uint8_t *key2,
						  uint8_t *key3,
						  uint8_t *iv,
						  uint32_t num);

void yd_tdes_cfb64_encrypt(uint8_t *in,
						   uint8_t *out,
						   uint8_t *key1,
						   uint8_t *key2,
						   uint8_t *key3,
						   uint8_t *iv,
						   uint32_t blk);
void yd_tdes_cfb64_decrypt(uint8_t *in,
						   uint8_t *out,
						   uint8_t *key1,
						   uint8_t *key2,
						   uint8_t *key3,
						   uint8_t *iv,
						   uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_TDES_CFB_H */
