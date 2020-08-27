
/* Apache License 2.0 */

/*
	文件：yd_des_ofb.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：DES算法模式OFB(Output Feedback)实现，详情参考《FIPS PUB 81》
	版本：README.md定义
*/

#ifndef YD_DES_OFB_H
#define YD_DES_OFB_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_des_ofb8_enc_dec_crypto(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t num);

void yd_des_ofb64_enc_dec_crypto(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_DES_OFB_H */
