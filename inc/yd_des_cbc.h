
/* ��ѣ������ */

/*
	�ļ���yd_des_cbc.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺DES�㷨ģʽCBC(Cipher Block Chaining)ʵ�֣�����ο���FIPS PUB 81��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#ifndef YD_DES_CBC_H
#define YD_DES_CBC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_des_cbc_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);
void yd_des_cbc_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_DES_CBC_H */
