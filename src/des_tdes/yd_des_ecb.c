
/* 免费，无许可 */

/*
	文件：yd_des_ecb.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：DES算法模式ECB(Electronic Codebook)实现，详情参考《FIPS PUB 81》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#include "yd_des_ecb.h"
#include "yd_des_base.h"


/*
	ECB模式，加密(注：按块加密，8字节的倍数)
	in： 待加密数据
	out：加密后数据
	key：8字节密钥
	blk：要加密的块数
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
	ECB模式，解密(注：按块解密，8字节的倍数)
	in： 待解密数据
	out：解密后数据
	key：8字节密钥
	blk：要解密的块数
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
