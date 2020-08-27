
/* Apache License 2.0 */

/*
	文件：yd_tdes_ofb.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：TDES算法模式OFB(Output Feedback)实现，详情参考《ANSI X9.52-1998》
	版本：README.md定义
*/

#include "yd_tdes_ofb.h"
#include "yd_des_base.h"


/*
 *	TOFB位模式，加(解)密(注：按块加(解)密，8字节的倍数)
 *	in： 待加(解)密数据
 *	out：解(加)密后数据
 *	key1：8字节密钥(注：只有三个密码不同时，才是三重DES)
 *	key2：8字节密钥
 *	key3：8字节密钥
 *	iv： 8字节初始矢量
 *	blk：要加(解)密的块数
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
		yd_des_crypto(iv_tmp, key3, DES_ENCRYPT); //加密后，再作为下次输入.
		for(i=0; i<8; i++)
		{
			out[i] = iv_tmp[i] ^ in[i]; //异或后，作为加密输出.
		}
		
		in += 8;
		out += 8;
		blk--;
	}
}
