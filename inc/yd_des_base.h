
/* Apache License 2.0 */

/*
	文件：yd_des_base.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：DES算法核心，详情参考《FIPS PUB46-3》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#ifndef YD_DES_BASE_H
#define YD_DES_BASE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


#define DES_ENCRYPT					0
#define DES_DECRYPT					1


void yd_des_crypto(uint8_t *in_out, uint8_t *key, uint8_t enc_dec);

#ifdef __cplusplus
}
#endif

#endif /* YD_DES_BASE_H */
