
/* Apache License 2.0 */

/*
	�ļ���yd_sha1.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺SHA1�㷨ʵ�֣�����ο���FIPS PUB 180-4��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#ifndef YD_SHA1_H
#define YD_SHA1_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


bool yd_sha1(uint8_t *message, uint32_t *sha1);

#ifdef __cplusplus
}
#endif

#endif /* YD_SHA1_H */
