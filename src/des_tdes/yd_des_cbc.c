
/* Apache License 2.0 */

/*
	�ļ���yd_des_cbc.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺DES�㷨ģʽCBC(Cipher Block Chaining)ʵ�֣�����ο���FIPS PUB 81��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_des_cbc.h"
#include "yd_des_base.h"


/*
	CBCģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_des_cbc_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i] ^ iv[i];
		}
		yd_des_crypto(out, key, DES_ENCRYPT);
		iv = out;

		in += 8;
		out += 8;
		blk--;
	}
}

/*
	CBCģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_des_cbc_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i];
		}
		yd_des_crypto(out, key, DES_DECRYPT);
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
