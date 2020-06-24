
/* ��ѣ������ */

/*
	�ļ���yd_tdes_ofb.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺TDES�㷨ģʽOFB(Output Feedback)ʵ�֣�����ο���ANSI X9.52-1998��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_tdes_ofb.h"
#include "yd_des_base.h"


/*
	TOFBλģʽ����(��)��(ע�������(��)�ܣ�8�ֽڵı���)
	in�� ����(��)������
	out����(��)�ܺ�����
	key1��8�ֽ���Կ(ע��ֻ���������벻ͬʱ����������DES)
	key2��8�ֽ���Կ
	key3��8�ֽ���Կ
	iv�� 8�ֽڳ�ʼʸ��
	blk��Ҫ��(��)�ܵĿ���
*/
void yd_tdes_ofb_enc_dec_crypto(uint8_t *in,
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
		yd_des_crypto(iv_tmp, key3, DES_ENCRYPT); //���ܺ�����Ϊ�´�����.
		for(i=0; i<8; i++)
		{
			out[i] = iv_tmp[i] ^ in[i]; //������Ϊ�������.
		}
		
		in += 8;
		out += 8;
		blk--;
	}
}
