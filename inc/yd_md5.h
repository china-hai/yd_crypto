
/* Apache License 2.0 */

/*
	文件：yd_md5.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：MD5算法实现，详情参考《RFC 1321》
	版本：README.md定义
*/

#ifndef YD_MD5_H
#define YD_MD5_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


bool yd_md5(uint8_t *message, uint8_t *md5);

#ifdef __cplusplus
}
#endif

#endif /* YD_MD5_H */
