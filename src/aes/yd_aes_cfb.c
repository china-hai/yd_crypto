
/* Apache License 2.0 */

/*
	�ļ���yd_aes_cfb.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺AES�㷨ģʽCFB(Cipher Feedback)ʵ�֣�����ο���SP800-38A��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_aes_cfb.h"
#include "yd_aes_base.h"


/*
	CFB-8λģʽ������(ע�����ֽڼ��ܣ�������8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key����Կ(4*AES_NK�ֽ�)
	iv�� 16�ֽڳ�ʼʸ��
	num��Ҫ���ܵ��ֽ���
*/
void yd_aes_cfb8_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t num)
{
	uint8_t i, iv_tmp1[16], iv_tmp2[16];
	uint32_t j;
	
	for(i=0; i<16; i++)
	{
		iv_tmp1[i] = iv[i];
		iv_tmp2[i] = iv[i]; //���ݵ�һ�������.
	}
	
	for(j=0; j<num; j++)
	{
		yd_aes_encrypt(iv_tmp1, key);
		out[j] = in[j] ^ iv_tmp1[0]; //�����Чλ.
		for(i=0; i<15; i++)
		{
			iv_tmp1[i] = iv_tmp2[i+1];
		}
		iv_tmp1[15] = out[j]; //����������ݣ���Ϊ�´������.
		
		for(i=0; i<16; i++)
		{
			iv_tmp2[i] = iv_tmp1[i]; //�ݴ棬��������´������.
		}
	}
}

/*
	CFB-8λģʽ������(ע�����ֽڽ��ܣ�������8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key����Կ(4*AES_NK�ֽ�)
	iv�� 16�ֽڳ�ʼʸ��
	num��Ҫ���ܵ��ֽ���
*/
void yd_aes_cfb8_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t num)
{
	uint8_t i, iv_tmp1[16], iv_tmp2[16];
	uint32_t j;
	
	for(i=0; i<16; i++)
	{
		iv_tmp1[i] = iv[i];
		iv_tmp2[i] = iv[i]; //���ݵ�һ�������.
	}
	
	for(j=0; j<num; j++)
	{
		yd_aes_encrypt(iv_tmp1, key); //ʹ�ü���ģʽ.
		out[j] = in[j] ^ iv_tmp1[0]; //�����Чλ.
		for(i=0; i<15; i++)
		{
			iv_tmp1[i] = iv_tmp2[i+1];
		}
		iv_tmp1[15] = in[j]; //���Ҫ�������ݣ���Ϊ�´������.
		
		for(i=0; i<16; i++)
		{
			iv_tmp2[i] = iv_tmp1[i]; //�ݴ棬��������´������.
		}
	}
}

/*
	CFB-128λģʽ������(ע��������ܣ�16�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key����Կ(4*AES_NK�ֽ�)
	iv�� 16�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_aes_cfb128_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i, iv_tmp[16];
	
	for(i=0; i<16; i++)
	{
		iv_tmp[i] = iv[i];
	}
	
	while(blk > 0)
	{
		yd_aes_encrypt(iv_tmp, key);
		for(i=0; i<16; i++)
		{
			iv_tmp[i] ^= in[i]; //�������������´������.
			out[i] = iv_tmp[i]; //ͬʱҲ�Ǽ����������.
		}
		
		in += 16;
		out += 16;
		blk--;
	}
}

/*
	CFB-128λģʽ������(ע��������ܣ�16�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key����Կ(4*AES_NK�ֽ�)
	iv�� 16�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_aes_cfb128_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i, iv_tmp[16];
	
	for(i=0; i<16; i++)
	{
		iv_tmp[i] = iv[i];
	}
	
	while(blk > 0)
	{
		yd_aes_encrypt(iv_tmp, key);
		for(i=0; i<16; i++)
		{
			out[i] = iv_tmp[i] ^ in[i]; //������Ϊ�������.
			iv_tmp[i] = in[i]; //�ϴ�Ҫ�������ݣ���Ϊ�´������.
		}
		
		in += 16;
		out += 16;
		blk--;
	}
}
