
/* Apache License 2.0 */

/*
	文件：yd_aes_base.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：AES算法核心，详情参考《FIPS PUB 197》
	版本：README.md定义
*/

#include "yd_aes_base.h"


static const uint8_t s_table[256] =
{
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
};

static const uint8_t inv_s_table[256] =
{
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d	
};

static uint8_t aes_key[(AES_NR+1)*16]; //保存扩展密钥.


/* 有限域GF(2^8表示2的8次方), 乘x(x多项式就是0x02) */
static uint8_t gf02(uint8_t x02)
{
	uint8_t tmp;
	
	/*
	 *	x02代表输入的多项式，x*b(x)的结果是x02 模mod 多项式{0x011b}=x^8 + x^4 + x^3 + x + 1
	 * 	可使用左移和异或0x1b实现，高位是0(小于0x80)直接左移1位，高位是1(大于等于0x80)先左移
	 *	1位，然后再异或0x1b
	 */
	tmp = x02 << 1;
	
	if(x02 >= 0x80)
	{
		tmp ^= 0x1b;
	}
	
	return tmp;
}

/* 两组数据异或 */
static void xor_bytes(uint8_t *ret, uint8_t *tmp, uint8_t num)
{
	uint8_t i;
	
	for(i=0; i<num; i++)
	{
		ret[i] ^= tmp[i];
	}	
}

/* 4字节转换 */
static void sub_word(uint8_t *word)
{
	uint8_t i, tmp;
	
	for(i=0; i<4; i++)
	{
		tmp = word[i];
		word[i] = s_table[tmp];
	}
}

/* 左旋转一个位置 */
static void rot_word(uint8_t *word)
{
	uint8_t tmp;
		
	tmp = word[0];
	word[0]  = word[1];
	word[1]  = word[2];
	word[2]  = word[3];
	word[3]  = tmp;
}

static void key_expansion(uint8_t *key)
{
	uint8_t i, j;
	uint8_t rcon[4] = {1, 0, 0, 0}; //x的0次方是1.
	uint8_t *p;
	
	for(i=0; i<4*AES_NK; i++)
	{
		aes_key[i] = key[i];
	}
	p = &aes_key[4*AES_NK]; //前16字节存储原始密钥，得到其后地址.
	
	for(i=AES_NK; i<4*(AES_NR+1); i++)
	{
		p -= 4;
		for(j=0; j<4; j++) //w[i-1].
		{
			p[j+4] = p[j];
		}
		
		p += 4;
		if(i % AES_NK == 0) //整数倍.
		{
			rot_word(p);
			sub_word(p);
			xor_bytes(p, rcon, 4);
			rcon[0] = gf02(rcon[0]); //有限域x{02}的指数幂.
		}
		else if((AES_NK == 8) && (i % AES_NK == 4))
		{
			sub_word(p);
		}
		else
		{}
			
		xor_bytes(p, p-4*AES_NK, 4); //与16个字节之前的异或.
			
		p += 4;
	}
}

/* 16字节替换 */
static void sub_bytes(uint8_t *state, uint8_t enc_dec)
{
	uint8_t i, tmp;
	const uint8_t *s;
	
	if(enc_dec == AES_ENCRYPT)
	{
		s = s_table;
	}
	else //解密.
	{
		s = inv_s_table;
	}
	
	for(i=0; i<16; i++) //字节置换.
	{
		tmp = state[i];
		state[i] = s[tmp];
	}
}

/* 行移位变换 */
static void shift_rows(uint8_t *state, uint8_t enc_dec)
{
	uint8_t tmp[3];
	
	/* 第一种算法实现，生成代码大概是第二种的一倍，执行速度比第二种快20%左右 */
	if(enc_dec == AES_ENCRYPT)
	{
		//第0行不变.
		tmp[0] = state[1];
		state[1] = state[5]; //第1行循环左移1次.
		state[5] = state[9];
		state[9] = state[13];
		state[13] = tmp[0];
		
		tmp[0] = state[2];
		tmp[1] = state[6];
		state[2] = state[10]; //第2行循环左移2次.
		state[6] = state[14];
		state[10] = tmp[0];
		state[14] = tmp[1];
		
		tmp[0] = state[3];
		tmp[1] = state[7];
		tmp[2] = state[11];
		state[3] = state[15]; //第3行循环左移3次.
		state[7] = tmp[0];
		state[11] = tmp[1];
		state[15] = tmp[2];
	}
	else //解密.
	{
		//第0行不变.
		tmp[0] = state[13];
		state[13] = state[9]; //第1行循环右移1次.
		state[9] = state[5];
		state[5] = state[1];
		state[1] = tmp[0];
		
		tmp[0] = state[10];
		tmp[1] = state[14];
		state[14] = state[6]; //第2行循环右移2次.
		state[10] = state[2];
		state[6] = tmp[1];
		state[2] = tmp[0];
		
		tmp[0] = state[7];
		tmp[1] = state[11];
		tmp[2] = state[15];
		state[15] = state[3]; //第3行循环右移3次.
		state[11] = tmp[2];
		state[7] = tmp[1];
		state[3] = tmp[0];
	}
	
	/* 第二种算法实现(参加网上代码) */
//	uint8_t row, column, tmp1, tmp2, tmprow[4];
//	
//	for(row=1; row<4; row++)
//	{
//		for(column=0; column<4; column++) /* 取一行进行移位 */
//		{
//			tmp1 = column*4 + row;
//			tmprow[column] = state[tmp1];
//		}
//		
//		for(column=0; column<4; column++) /* 移位一行 */
//		{
//			if(enc_dec == AES_ENCRYPT)
//			{
//				tmp1 = (row + column) % 4;
//			}
//			else
//			{
//				tmp1 = (4 - row + column) % 4;
//			}
//			tmp2 = column*4 + row;
//			state[tmp2] = tmprow[tmp1];
//		}
//	}	
}

/* 列混合 */
static void mix_columns(uint8_t *state, uint8_t enc_dec)
{
	uint8_t i, tmp, column[4];
	uint8_t s02m4, s13m4;
	
	for(i=0; i<4; i++)
	{
		/*
		 *	GF有限域加法(异或运算)
		 *	b(x) = {03}x^3 + {01}x^2 + {01}x + {02} (AES算法选择的固定4项多项式)
		 *	它的逆多项式 = {0b}x^3 + {0d}x^2 + {09}x + {0e}
		 *	b(x) X(取模乘) s(x)可以写成矩阵，多项式表示如下
		 *	s'0 = 2s0 + 3s1 + s2 + s3 = 2s0 + 2s1 + s2 + s3 + s1 = 2(s0 + s1) + (s1 + s2 + s3)
		 *	s'1 = s0 + 2s1 + 3s2 + s3 = 2s1 + 2s2 + s0 + s3 + s2 = 2(s1 + s2) + (s0 + s2 + s3)
		 *	s'2 = s0 + s1 + 2s2 + 3s3 = 2s2 + 2s3 + s0 + s1 + s3 = 2(s2 + s3) + (s0 + s1 + s3)
		 *	s'3 = 3s0 + s1 + s2 + 2s3 = 2s3 + 2s0 + s1 + s2 + s0 = 2(s3 + s0) + (s0 + s1 + s2)
		 */
		
		/* 为优化执行速度(参考网上代码)，如：s1+s2+s3加入s0，然后再加s0，因为s0异或s0就是0 */
		tmp = state[0] ^ state[1] ^ state[2] ^ state[3];
		
		column[0] = tmp ^ state[0] ^ gf02(state[0] ^ state[1]);
		column[1] = tmp ^ state[1] ^ gf02(state[1] ^ state[2]);
		column[2] = tmp ^ state[2] ^ gf02(state[2] ^ state[3]);
		column[3] = tmp ^ state[3] ^ gf02(state[3] ^ state[0]);
		
		if(enc_dec == AES_DECRYPT) //解密.
		{
			/*
			 *	b(x)的逆多项式 = {0b}x^3 + {0d}x^2 + {09}x + {0e}
			 *	b(x)的逆 X(取模乘) s(x)可以写成矩阵，多项式表示如下
			 *	s'0 = 14s0 + 11s1 + 13s2 + 9s3
			 *	s'1 = 9s0 + 14s1 + 11s2 + 13s3
			 *	s'2 = 13s0 + 9s1 + 14s2 + 11s3
			 *	s'3 = 11s0 + 13s1 + 9s2 + 14s3
			 */
			
			/*
			 *	为优化执行速度(参考网上代码)，如s'0 = 14s0 + 11s1 + 13s2 + 9s3
			 *	= 2(s0 + s1) + (s0 + s1 + s2 + s3) + s0 //加密部分实现
			 *	+ 2[4(a0 + a2) + 4(a1 + a3)] + 4(a0 + a2)
			 */
			s02m4 = gf02(gf02(state[0] ^ state[2]));
			s13m4 = gf02(gf02(state[1] ^ state[3]));
			tmp = gf02(s02m4 ^ s13m4);
			
			column[0] ^= tmp ^ s02m4;
			column[1] ^= tmp ^ s13m4;
			column[2] ^= tmp ^ s02m4;
			column[3] ^= tmp ^ s13m4;
		}
		
		state[0] = column[0];
		state[1] = column[1];
		state[2] = column[2];
		state[3] = column[3];
		
		state += 4;
	}
}

/* 轮密钥加变换 */
static void add_round_key(uint8_t *state, uint8_t *key)
{
	xor_bytes(state, key, 16);
}

/* 块（16B）加密 */
void yd_aes_encrypt(uint8_t *state, uint8_t *key)
{
	uint8_t i;
	
	key_expansion(key); //扩展密钥.
	
	add_round_key(state, aes_key);
	for(i=1; i<AES_NR; i++)
	{
		sub_bytes(state, AES_ENCRYPT);
		shift_rows(state, AES_ENCRYPT);
		mix_columns(state, AES_ENCRYPT);
		add_round_key(state, &aes_key[i*16]);
	}
	sub_bytes(state, AES_ENCRYPT);
	shift_rows(state, AES_ENCRYPT);
	add_round_key(state, &aes_key[AES_NR*16]);
}

/* 块（16B）解密 */
void yd_aes_decrypt(uint8_t *state, uint8_t *key)
{
	uint8_t i;
	
	key_expansion(key); //扩展密钥.
	
	add_round_key(state, &aes_key[AES_NR*16]);
	for(i=AES_NR; i>1; i--)
	{
		shift_rows(state, AES_DECRYPT);
		sub_bytes(state, AES_DECRYPT);
		add_round_key(state, &aes_key[16*(i-1)]);
		mix_columns(state, AES_DECRYPT);
	}
	shift_rows(state, AES_DECRYPT);
	sub_bytes(state, AES_DECRYPT);
	add_round_key(state, aes_key);
}
