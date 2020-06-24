
/* 免费，无许可 */

/*
	文件：yd_aes_ofb.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：AES算法模式OFB(Output Feedback)实现，详情参考《SP800-38A》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#include "yd_aes_ofb.h"
#include "yd_aes_base.h"


/*
	OFB模式，加(解)密(注：按块加(解)密，16字节的倍数)
	in： 待加(解)密数据
	out：解(加)密后数据
	key：密钥(4*AES_NK字节)
	iv： 16字节初始矢量
	blk：要加(解)密的块数
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
		yd_aes_encrypt(iv_tmp, key); //加密后，再作为下次输入.
		for(i=0; i<16; i++)
		{
			out[i] = iv_tmp[i] ^ in[i]; //异或后，作为加密输出.
		}
		
		in += 16;
		out += 16;
		blk--;
	}
}
