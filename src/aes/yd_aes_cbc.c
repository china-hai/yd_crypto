
/* Apache License 2.0 */

/*
	文件：yd_aes_cbc.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：AES算法模式CBC(Cipher Block Chaining)实现，详情参考《SP800-38A》
	版本：README.md定义
*/

#include "yd_aes_cbc.h"
#include "yd_aes_base.h"


/*
 *	CBC模式，加密(注：按块加密，16字节的倍数)
 *	in： 待加密数据
 *	out：加密后数据
 *	key：密钥(4*AES_NK字节)
 *	iv： 16字节初始矢量
 *	blk：要加密的块数
 */
void yd_aes_cbc_encrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<16; i++)
		{
			out[i] = in[i] ^ iv[i];
		}
		yd_aes_encrypt(out, key);
		iv = out;
		
		in += 16;
		out += 16;
		blk--;
	}
}

/*
 *	CBC模式，解密(注：按块解密，16字节的倍数)
 *	in： 待解密数据
 *	out：解密后数据
 *	key：密钥(4*AES_NK字节)
 *	iv： 16字节初始矢量
 *	blk：要解密的块数
 */
void yd_aes_cbc_decrypt(uint8_t *in, uint8_t *out, uint8_t *key, uint8_t *iv, uint32_t blk)
{
	uint8_t i;
	
	while(blk > 0)
	{
		for(i=0; i<16; i++)
		{
			out[i] = in[i];
		}
		yd_aes_decrypt(out, key);
		for(i=0; i<16; i++)
		{
			out[i] ^= iv[i];
		}
		iv = in;
		
		in += 16;
		out += 16;
		blk--;
	}
}
