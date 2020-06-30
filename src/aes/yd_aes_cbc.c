
/* Apache License 2.0 */

/*
	�ļ���yd_aes_cbc.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺AES�㷨ģʽCBC(Cipher Block Chaining)ʵ�֣�����ο���SP800-38A��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_aes_cbc.h"
#include "yd_aes_base.h"


/*
	CBCģʽ������(ע��������ܣ�16�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key����Կ(4*AES_NK�ֽ�)
	iv�� 16�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_aes_cbc_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<16; i++)
		{
			out[i] = in[i] ^ iv[i];
		}
		yd_aes_encrypt(out, key);
		iv = out;
		
		in += 16;
		out += 16;
		blk--;
	}
}

/*
	CBCģʽ������(ע��������ܣ�16�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key����Կ(4*AES_NK�ֽ�)
	iv�� 16�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_aes_cbc_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<16; i++)
		{
			out[i] = in[i];
		}
		yd_aes_decrypt(out, key);
		for(i=0; i<16; i++)
		{
			out[i] ^= iv[i];
		}
		iv = in;
		
		in += 16;
		out += 16;
		blk--;
	}
}
