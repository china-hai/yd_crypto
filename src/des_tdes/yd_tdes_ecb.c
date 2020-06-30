
/* Apache License 2.0 */

/*
	�ļ���yd_tdes_ecb.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺TDES�㷨ģʽECB(Electronic Codebook)ʵ�֣�����ο���ANSI X9.52-1998��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_tdes_ecb.h"
#include "yd_des_base.h"


/*
	TECBģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key1��8�ֽ���Կ(ע��ֻ���������벻ͬʱ����������DES)
	key2��8�ֽ���Կ
	key3��8�ֽ���Կ
	blk��Ҫ���ܵĿ���
*/
void yd_tdes_ecb_encrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i];
		}
		yd_des_crypto(out, key1, DES_ENCRYPT);
		yd_des_crypto(out, key2, DES_DECRYPT);
		yd_des_crypto(out, key3, DES_ENCRYPT);
		
		in += 8;
		out += 8;
		blk--;
	}
}

/*
	TECBģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key1��8�ֽ���Կ(ע��ֻ���������벻ͬʱ����������DES)
	key2��8�ֽ���Կ
	key3��8�ֽ���Կ
	blk��Ҫ���ܵĿ���
*/
void yd_tdes_ecb_decrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i];
		}
		yd_des_crypto(out, key3, DES_DECRYPT);
		yd_des_crypto(out, key2, DES_ENCRYPT);
		yd_des_crypto(out, key1, DES_DECRYPT);
		
		in += 8;
		out += 8;
		blk--;
	}
}
