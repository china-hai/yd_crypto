
/* Apache License 2.0 */

/*
	�ļ���yd_sm3.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺SM3�㷨ʵ�֣�����ο���SM3 GM/T 0004-2012��
	�汾��V1.0.01
*/

/*
	2020-6-29����һ�η���.
*/

#ifndef YD_SM3_H
#define YD_SM3_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


bool yd_sm3(uint8_t *message, uint32_t *sm3);

#ifdef __cplusplus
}
#endif

#endif /* YD_SM3_H */
