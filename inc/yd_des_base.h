
/* Apache License 2.0 */

/*
	�ļ���yd_des_base.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺DES�㷨���ģ�����ο���FIPS PUB46-3��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
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
