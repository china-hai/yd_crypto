
/* Apache License 2.0 */

/*
	文件：yd_des_ecb.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：DES算法模式ECB(Electronic Codebook)实现，详情参考《FIPS PUB 81》
	版本：README.md定义
*/

#ifndef YD_DES_ECB_H
#define YD_DES_ECB_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_des_ecb_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint32_t blk);
void yd_des_ecb_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_DES_ECB_H */
