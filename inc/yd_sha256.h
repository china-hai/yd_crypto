
/* 免费，无许可 */

/*
	文件：yd_sha256.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：SHA256算法实现，详情参考《FIPS PUB 180-4》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#ifndef YD_SHA256_H
#define YD_SHA256_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


bool yd_sha256(uint8_t *message, uint32_t *sha256);

#ifdef __cplusplus
}
#endif

#endif /* YD_SHA256_H */
