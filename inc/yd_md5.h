
/* ��ѣ������ */

/*
	�ļ���yd_md5.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺MD5�㷨ʵ�֣�����ο���RFC 1321��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
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
