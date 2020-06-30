
/* Apache License 2.0 */

/*
	文件：yd_tdes_cbc.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：TDES算法模式CBC(Cipher Block Chaining)实现，详情参考《ANSI X9.52-1998》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#include "yd_tdes_cbc.h"
#include "yd_des_base.h"


/*
	TCBC模式，加密(注：按块加密，8字节的倍数)
	in： 待加密数据
	out：加密后数据
	key1：8字节密钥(注：只有三个密码不同时，才是三重DES)
	key2：8字节密钥
	key3：8字节密钥
	iv： 8字节初始矢量
	blk：要加密的块数
*/
void yd_tdes_cbc_encrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint8_t *iv,
						 uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<8; i++)
		{
			out[i] = in[i] ^ iv[i];
		}
		yd_des_crypto(out, key1, DES_ENCRYPT);
		yd_des_crypto(out, key2, DES_DECRYPT);
		yd_des_crypto(out, key3, DES_ENCRYPT);
		iv = out;

		in += 8;
		out += 8;
		blk--;
	}
}

/*
	TCBC模式，解密(注：按块解密，8字节的倍数)
	in： 待解密数据
	out：解密后数据
	key1：8字节密钥(注：只有三个密码不同时，才是三重DES)
	key2：8字节密钥
	key3：8字节密钥
	iv： 8字节初始矢量
	blk：要解密的块数
*/
void yd_tdes_cbc_decrypt(uint8_t *in,
						 uint8_t *out,
						 uint8_t *key1,
						 uint8_t *key2,
						 uint8_t *key3,
						 uint8_t *iv,
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
		for(i=0; i<8; i++)
		{
			out[i] ^= iv[i];
		}
		iv = in;

		in += 8;
		out += 8;
		blk--;
	}
}
