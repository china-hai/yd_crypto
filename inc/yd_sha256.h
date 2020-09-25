
/* Apache License 2.0 */

/*
	文件：yd_sha256.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：SHA256算法实现，详情参考《FIPS PUB 180-4》
	版本：README.md定义
*/

#ifndef YD_SHA256_H
#define YD_SHA256_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


bool yd_sha256(uint8_t *msg, uint32_t msg_length, uint32_t *sha256);

#ifdef __cplusplus
}
#endif

#endif /* YD_SHA256_H */
