
/* Apache License 2.0 */

/*
	文件：yd_tdes_ecb.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：TDES算法模式ECB(Electronic Codebook)实现，详情参考《ANSI X9.52-1998》
	版本：README.md定义
*/

#include "yd_tdes_ecb.h"
#include "yd_des_base.h"


/*
 *	TECB模式，加密(注：按块加密，8字节的倍数)
 *	in： 待加密数据
 *	out：加密后数据
 *	key1：8字节密钥(注：只有三个密码不同时，才是三重DES)
 *	key2：8字节密钥
 *	key3：8字节密钥
 *	blk：要加密的块数
 */
void yd_tdes_ecb_encrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i];
		}
		yd_des_crypto(out, key1, DES_ENCRYPT);
		yd_des_crypto(out, key2, DES_DECRYPT);
		yd_des_crypto(out, key3, DES_ENCRYPT);
		
		in += 8;
		out += 8;
		blk--;
	}
}

/*
 *	TECB模式，解密(注：按块解密，8字节的倍数)
 *	in： 待解密数据
 *	out：解密后数据
 *	key1：8字节密钥(注：只有三个密码不同时，才是三重DES)
 *	key2：8字节密钥
 *	key3：8字节密钥
 *	blk：要解密的块数
 */
void yd_tdes_ecb_decrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i];
		}
		yd_des_crypto(out, key3, DES_DECRYPT);
		yd_des_crypto(out, key2, DES_ENCRYPT);
		yd_des_crypto(out, key1, DES_DECRYPT);
		
		in += 8;
		out += 8;
		blk--;
	}
}
