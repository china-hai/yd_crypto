
/* Apache License 2.0 */

/*
	文件：yd_sm3.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：SM3算法实现，详情参考《SM3 GM/T 0004-2012》
	版本：README.md定义
*/

#ifndef YD_SM3_H
#define YD_SM3_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


bool yd_sm3(uint8_t *msg, uint32_t msg_length, uint32_t *sm3);

#ifdef __cplusplus
}
#endif

#endif /* YD_SM3_H */
