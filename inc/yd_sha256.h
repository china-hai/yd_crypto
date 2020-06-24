
/* ��ѣ������ */

/*
	�ļ���yd_sha256.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺SHA256�㷨ʵ�֣�����ο���FIPS PUB 180-4��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
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
