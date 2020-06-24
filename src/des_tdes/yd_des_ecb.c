
/* ��ѣ������ */

/*
	�ļ���yd_des_ecb.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺DES�㷨ģʽECB(Electronic Codebook)ʵ�֣�����ο���FIPS PUB 81��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_des_ecb.h"
#include "yd_des_base.h"


/*
	ECBģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key��8�ֽ���Կ
	blk��Ҫ���ܵĿ���
*/
void yd_des_ecb_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i];
		}
		yd_des_crypto(out, key, DES_ENCRYPT);
		
		in += 8;
		out += 8;
		blk--;
	}
}

/*
	ECBģʽ������(ע��������ܣ�8�ֽڵı���)
	in�� ����������
	out�����ܺ�����
	key��8�ֽ���Կ
	blk��Ҫ���ܵĿ���
*/
void yd_des_ecb_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i];
		}
		yd_des_crypto(out, key, DES_DECRYPT);
		
		in += 8;
		out += 8;
		blk--;
	}
}
