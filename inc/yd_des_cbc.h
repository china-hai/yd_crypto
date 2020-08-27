
/* Apache License 2.0 */

/*
	文件：yd_des_cbc.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：DES算法模式CBC(Cipher Block Chaining)实现，详情参考《FIPS PUB 81》
	版本：README.md定义
*/

#ifndef YD_DES_CBC_H
#define YD_DES_CBC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_des_cbc_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);
void yd_des_cbc_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_DES_CBC_H */
