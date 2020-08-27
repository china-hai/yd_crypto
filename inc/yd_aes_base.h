
/* Apache License 2.0 */

/*
	文件：yd_aes_base.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：AES算法核心，详情参考《FIPS PUB 197》
	版本：README.md定义
*/

#ifndef YD_AES_BASE_H
#define YD_AES_BASE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


#define AES_ENCRYPT					0
#define AES_DECRYPT					1

#define AES_NK						4 //4个字(16字节).
//#define AES_NK					6 //6个字(24字节).
//#define AES_NK					8 //8个字(32字节).

#if AES_NK == 4
	#define AES_NR					10 //运算轮数.
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
