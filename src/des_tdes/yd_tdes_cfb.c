
/* Apache License 2.0 */

/*
	�ļ���yd_tdes_cfb.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺TDES�㷨ģʽCFB(Cipher Feedback)ʵ�֣�����ο���ANSI X9.52-1998��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_tdes_cfb.h"
#include "yd_des_base.h"


/*
	TCFB-8λģʽ������(ע�����ֽڼ��ܣ�������8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key1��8�ֽ���Կ(ע��ֻ���������벻ͬʱ����������DES)
	key2��8�ֽ���Կ
	key3��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	num��Ҫ���ܵ��ֽ���
*/
void yd_tdes_cfb8_encrypt(uint8_t *in,
						  uint8_t *out,
						  uint8_t *key1,
						  uint8_t *key2,
						  uint8_t *key3,
						  uint8_t *iv,
						  uint32_t num)
{
	uint8_t i, iv_tmp1[8], iv_tmp2[8];
	uint32_t j;
	
	for(i=0; i<8; i++)
	{
		iv_tmp1[i] = iv[i];
		iv_tmp2[i] = iv[i]; //���ݵ�һ�������.
	}
	
	for(j=0; j<num; j++)
	{
		yd_des_crypto(iv_tmp1, key1, DES_ENCRYPT);
		yd_des_crypto(iv_tmp1, key2, DES_DECRYPT);
		yd_des_crypto(iv_tmp1, key3, DES_ENCRYPT);
		out[j] = in[j] ^ iv_tmp1[0]; //�����Чλ.
		for(i=0; i<7; i++)
		{
			iv_tmp1[i] = iv_tmp2[i+1];
		}
		iv_tmp1[7] = out[j]; //����������ݣ���Ϊ�´������.
		
		for(i=0; i<8; i++)
		{
			iv_tmp2[i] = iv_tmp1[i]; //�ݴ棬��������´������.
		}
	}
}

/*
	TCFB-8λģʽ������(ע�����ֽڽ��ܣ�������8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key1��8�ֽ���Կ(ע��ֻ���������벻ͬʱ����������DES)
	key2��8�ֽ���Կ
	key3��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	num��Ҫ���ܵ��ֽ���
*/
void yd_tdes_cfb8_decrypt(uint8_t *in,
						  uint8_t *out,
						  uint8_t *key1,
						  uint8_t *key2,
						  uint8_t *key3,
						  uint8_t *iv,
						  uint32_t num)
{
	uint8_t i, iv_tmp1[8], iv_tmp2[8];
	uint32_t j;
	
	for(i=0; i<8; i++)
	{
		iv_tmp1[i] = iv[i];
		iv_tmp2[i] = iv[i]; //���ݵ�һ�������.
	}
	
	for(j=0; j<num; j++)
	{
		yd_des_crypto(iv_tmp1, key1, DES_ENCRYPT);
		yd_des_crypto(iv_tmp1, key2, DES_DECRYPT);
		yd_des_crypto(iv_tmp1, key3, DES_ENCRYPT);
		out[j] = in[j] ^ iv_tmp1[0]; //�����Чλ.
		for(i=0; i<7; i++)
		{
			iv_tmp1[i] = iv_tmp2[i+1];
		}
		iv_tmp1[7] = in[j]; //���Ҫ�������ݣ���Ϊ�´������.
		
		for(i=0; i<8; i++)
		{
			iv_tmp2[i] = iv_tmp1[i]; //�ݴ棬��������´������.
		}
	}
}

/*
	TCFB-64λģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key1��8�ֽ���Կ(ע��ֻ���������벻ͬʱ����������DES)
	key2��8�ֽ���Կ
	key3��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_tdes_cfb64_encrypt(uint8_t *in,
						   uint8_t *out,
						   uint8_t *key1,
						   uint8_t *key2,
						   uint8_t *key3,
						   uint8_t *iv,
						   uint32_t blk)
{
	uint8_t i, iv_tmp[8];
	
	for(i=0; i<8; i++)
	{
		iv_tmp[i] = iv[i];
	}
	
	while(blk > 0)
	{
		yd_des_crypto(iv_tmp, key1, DES_ENCRYPT);
		yd_des_crypto(iv_tmp, key2, DES_DECRYPT);
		yd_des_crypto(iv_tmp, key3, DES_ENCRYPT);
		for(i=0; i<8; i++)
		{
			iv_tmp[i] ^= in[i]; //�������������´������.
			out[i] = iv_tmp[i]; //ͬʱҲ�Ǽ����������.
		}
		
		in += 8;
		out += 8;
		blk--;
	}
}

/*
	TCFB-64λģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key1��8�ֽ���Կ(ע��ֻ���������벻ͬʱ����������DES)
	key2��8�ֽ���Կ
	key3��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	blk��Ҫ���ܵĿ���
*/
void yd_tdes_cfb64_decrypt(uint8_t *in,
						   uint8_t *out,
						   uint8_t *key1,
						   uint8_t *key2,
						   uint8_t *key3,
						   uint8_t *iv,
						   uint32_t blk)
{
	uint8_t i, iv_tmp[8];
	
	for(i=0; i<8; i++)
	{
		iv_tmp[i] = iv[i];
	}
	
	while(blk > 0)
	{
		yd_des_crypto(iv_tmp, key1, DES_ENCRYPT);
		yd_des_crypto(iv_tmp, key2, DES_DECRYPT);
		yd_des_crypto(iv_tmp, key3, DES_ENCRYPT);
		for(i=0; i<8; i++)
		{
			out[i] = iv_tmp[i] ^ in[i]; //������Ϊ�������.
			iv_tmp[i] = in[i]; //�ϴ�Ҫ�������ݣ���Ϊ�´������.
		}
		
		in += 8;
		out += 8;
		blk--;
	}
}
