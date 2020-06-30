
/* Apache License 2.0 */

/*
	�ļ���yd_des_ofb.h
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺DES�㷨ģʽOFB(Output Feedback)ʵ�֣�����ο���FIPS PUB 81��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#ifndef YD_DES_OFB_H
#define YD_DES_OFB_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>


void yd_des_ofb8_enc_dec_crypto(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t num);

void yd_des_ofb64_enc_dec_crypto(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk);

#ifdef __cplusplus
}
#endif

#endif /* YD_DES_OFB_H */
