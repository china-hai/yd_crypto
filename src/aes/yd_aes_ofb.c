
/* ��ѣ������ */

/*
	�ļ���yd_aes_ofb.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺AES�㷨ģʽOFB(Output Feedback)ʵ�֣�����ο���SP800-38A��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_aes_ofb.h"
#include "yd_aes_base.h"


/*
	OFBģʽ����(��)��(ע�������(��)�ܣ�16�ֽڵı���)
	in�� ����(��)������
	out����(��)�ܺ�����
	key����Կ(4*AES_NK�ֽ�)
	iv�� 16�ֽڳ�ʼʸ��
	blk��Ҫ��(��)�ܵĿ���
*/
void yd_aes_ofb_enc_dec_crypto(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i, iv_tmp[16];
	
	for(i=0; i<16; i++)
	{
		iv_tmp[i] = iv[i];
	}
	
	while(blk > 0)
	{
		yd_aes_encrypt(iv_tmp, key); //���ܺ�����Ϊ�´�����.
		for(i=0; i<16; i++)
		{
			out[i] = iv_tmp[i] ^ in[i]; //������Ϊ�������.
		}
		
		in += 16;
		out += 16;
		blk--;
	}
}
