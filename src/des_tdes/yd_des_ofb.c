
/* Apache License 2.0 */

/*
	文件：yd_des_ofb.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：DES算法模式OFB(Output Feedback)实现，详情参考《FIPS PUB 81》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#include "yd_des_ofb.h"
#include "yd_des_base.h"


/*
	OFB-8位模式，加(解)密(注：按字节加(解)密，不用是8字节的倍数)
	in： 待加(解)密数据
	out：解(加)密后数据
	key：8字节密钥
	iv： 8字节初始矢量
	num：要加(解)密的字节数
*/
void yd_des_ofb8_enc_dec_crypto(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t num)
{
	uint8_t i, iv_tmp1[8], iv_tmp2[8];
	uint32_t j;
	
	for(i=0; i<8; i++)
	{
		iv_tmp1[i] = iv[i];
		iv_tmp2[i] = iv[i]; //备份第一次输入块.
	}
	
	for(j=0; j<num; j++)
	{
		yd_des_crypto(iv_tmp1, key, DES_ENCRYPT);
		out[j] = in[j] ^ iv_tmp1[0]; //最高有效位.
		iv_tmp2[0] = iv_tmp1[0];
		for(i=0; i<7; i++)
		{
			iv_tmp1[i] = iv_tmp2[i+1];
		}
		iv_tmp1[7] = iv_tmp2[0]; //组合加密后的数据，作为下次输入块.
		
		for(i=0; i<8; i++)
		{
			iv_tmp2[i] = iv_tmp1[i]; //暂存，用于组合下次输入块.
		}
	}
}

/*
	OFB-64位模式，加(解)密(注：按块加(解)密，8字节的倍数)
	in： 待加(解)密数据
	out：解(加)密后数据
	key：8字节密钥
	iv： 8字节初始矢量
	blk：要加(解)密的块数
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
		yd_des_crypto(iv_tmp, key, DES_ENCRYPT); //加密后，再作为下次输入.
		for(i=0; i<8; i++)
		{
			out[i] = iv_tmp[i] ^ in[i]; //异或后，作为加密输出.
		}
		
		in += 8;
		out += 8;
		blk--;
	}
}
