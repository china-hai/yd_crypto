
/* Apache License 2.0 */

/*
	文件：yd_tdes_cfb.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：TDES算法模式CFB(Cipher Feedback)实现，详情参考《ANSI X9.52-1998》
	版本：README.md定义
*/

#include "yd_tdes_cfb.h"
#include "yd_des_base.h"


/*
 *	TCFB-8位模式，加密(注：按字节加密，不用是8字节的倍数)
 *	in： 待加密数据
 *	out：加密后数据
 *	key1：8字节密钥(注：只有三个密码不同时，才是三重DES)
 *	key2：8字节密钥
 *	key3：8字节密钥
 *	iv： 8字节初始矢量
 *	num：要加密的字节数
 */
void yd_tdes_cfb8_encrypt(uint8_t *in,
						  uint8_t *out,
						  uint8_t *key1,
						  uint8_t *key2,
						  uint8_t *key3,
						  uint8_t *iv,
						  uint32_t num)
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
		yd_des_crypto(iv_tmp1, key1, DES_ENCRYPT);
		yd_des_crypto(iv_tmp1, key2, DES_DECRYPT);
		yd_des_crypto(iv_tmp1, key3, DES_ENCRYPT);
		out[j] = in[j] ^ iv_tmp1[0]; //最高有效位.
		for(i=0; i<7; i++)
		{
			iv_tmp1[i] = iv_tmp2[i+1];
		}
		iv_tmp1[7] = out[j]; //组合密文数据，作为下次输入块.
		
		for(i=0; i<8; i++)
		{
			iv_tmp2[i] = iv_tmp1[i]; //暂存，用于组合下次输入块.
		}
	}
}

/*
 *	TCFB-8位模式，解密(注：按字节解密，不用是8字节的倍数)
 *	in： 待解密数据
 *	out：解密后数据
 *	key1：8字节密钥(注：只有三个密码不同时，才是三重DES)
 *	key2：8字节密钥
 *	key3：8字节密钥
 *	iv： 8字节初始矢量
 *	num：要解密的字节数
 */
void yd_tdes_cfb8_decrypt(uint8_t *in,
						  uint8_t *out,
						  uint8_t *key1,
						  uint8_t *key2,
						  uint8_t *key3,
						  uint8_t *iv,
						  uint32_t num)
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
		yd_des_crypto(iv_tmp1, key1, DES_ENCRYPT);
		yd_des_crypto(iv_tmp1, key2, DES_DECRYPT);
		yd_des_crypto(iv_tmp1, key3, DES_ENCRYPT);
		out[j] = in[j] ^ iv_tmp1[0]; //最高有效位.
		for(i=0; i<7; i++)
		{
			iv_tmp1[i] = iv_tmp2[i+1];
		}
		iv_tmp1[7] = in[j]; //组合要解密数据，作为下次输入块.
		
		for(i=0; i<8; i++)
		{
			iv_tmp2[i] = iv_tmp1[i]; //暂存，用于组合下次输入块.
		}
	}
}

/*
 *	TCFB-64位模式，加密(注：按块加密，8字节的倍数)
 *	in： 待加密数据
 *	out：加密后数据
 *	key1：8字节密钥(注：只有三个密码不同时，才是三重DES)
 *	key2：8字节密钥
 *	key3：8字节密钥
 *	iv： 8字节初始矢量
 *	blk：要加密的块数
 */
void yd_tdes_cfb64_encrypt(uint8_t *in,
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
		yd_des_crypto(iv_tmp, key3, DES_ENCRYPT);
		for(i=0; i<8; i++)
		{
			iv_tmp[i] ^= in[i]; //和明文异或后，做下次输入块.
			out[i] = iv_tmp[i]; //同时也是加密输出数据.
		}
		
		in += 8;
		out += 8;
		blk--;
	}
}

/*
 *	TCFB-64位模式，解密(注：按块解密，8字节的倍数)
 *	in： 待解密数据
 *	out：解密后数据
 *	key1：8字节密钥(注：只有三个密码不同时，才是三重DES)
 *	key2：8字节密钥
 *	key3：8字节密钥
 *	iv： 8字节初始矢量
 *	blk：要解密的块数
 */
void yd_tdes_cfb64_decrypt(uint8_t *in,
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
		yd_des_crypto(iv_tmp, key3, DES_ENCRYPT);
		for(i=0; i<8; i++)
		{
			out[i] = iv_tmp[i] ^ in[i]; //异或后，作为解密输出.
			iv_tmp[i] = in[i]; //上次要解密数据，作为下次输入块.
		}
		
		in += 8;
		out += 8;
		blk--;
	}
}
