
/* Apache License 2.0 */

/*
	�ļ���yd_des_ofb.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺DES�㷨ģʽOFB(Output Feedback)ʵ�֣�����ο���FIPS PUB 81��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_des_ofb.h"
#include "yd_des_base.h"


/*
	OFB-8λģʽ����(��)��(ע�����ֽڼ�(��)�ܣ�������8�ֽڵı���)
	in�� ����(��)������
	out����(��)�ܺ�����
	key��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	num��Ҫ��(��)�ܵ��ֽ���
*/
void yd_des_ofb8_enc_dec_crypto(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t num)
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
		yd_des_crypto(iv_tmp1, key, DES_ENCRYPT);
		out[j] = in[j] ^ iv_tmp1[0]; //�����Чλ.
		iv_tmp2[0] = iv_tmp1[0];
		for(i=0; i<7; i++)
		{
			iv_tmp1[i] = iv_tmp2[i+1];
		}
		iv_tmp1[7] = iv_tmp2[0]; //��ϼ��ܺ�����ݣ���Ϊ�´������.
		
		for(i=0; i<8; i++)
		{
			iv_tmp2[i] = iv_tmp1[i]; //�ݴ棬��������´������.
		}
	}
}

/*
	OFB-64λģʽ����(��)��(ע�������(��)�ܣ�8�ֽڵı���)
	in�� ����(��)������
	out����(��)�ܺ�����
	key��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	blk��Ҫ��(��)�ܵĿ���
*/
void yd_des_ofb64_enc_dec_crypto(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i, iv_tmp[8];
	
	for(i=0; i<8; i++)
	{
		iv_tmp[i] = iv[i];
	}
	
	while(blk > 0)
	{
		yd_des_crypto(iv_tmp, key, DES_ENCRYPT); //���ܺ�����Ϊ�´�����.
		for(i=0; i<8; i++)
		{
			out[i] = iv_tmp[i] ^ in[i]; //������Ϊ�������.
		}
		
		in += 8;
		out += 8;
		blk--;
	}
}
