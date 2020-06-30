
/* Apache License 2.0 */

/*
	�ļ���yd_tdes_cbc.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺TDES�㷨ģʽCBC(Cipher Block Chaining)ʵ�֣�����ο���ANSI X9.52-1998��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_tdes_cbc.h"
#include "yd_des_base.h"


/*
	TCBCģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key1��8�ֽ���Կ(ע��ֻ���������벻ͬʱ����������DES)
	key2��8�ֽ���Կ
	key3��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_tdes_cbc_encrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint8_t *iv,
						 uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i] ^ iv[i];
		}
		yd_des_crypto(out, key1, DES_ENCRYPT);
		yd_des_crypto(out, key2, DES_DECRYPT);
		yd_des_crypto(out, key3, DES_ENCRYPT);
		iv = out;

		in += 8;
		out += 8;
		blk--;
	}
}

/*
	TCBCģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key1��8�ֽ���Կ(ע��ֻ���������벻ͬʱ����������DES)
	key2��8�ֽ���Կ
	key3��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_tdes_cbc_decrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint8_t *iv,
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
		for(i=0; i<8; i++)
		{
			out[i] ^= iv[i];
		}
		iv = in;

		in += 8;
		out += 8;
		blk--;
	}
}
