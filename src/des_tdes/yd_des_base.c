
/* 免费，无许可 */

/*
	文件：yd_des_base.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：DES算法核心，详情参考《FIPS PUB46-3》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#include "yd_des_base.h"


static const uint8_t s_table[8][64]=
{
	14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, //S1.
	0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
	4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
	15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
	
	15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, //S2.
	3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
	0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
	13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
	
	10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, //S3.
	13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
	13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
	1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
	
	7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, //S4.
	13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
	10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
	3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
	
	2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, //S5.
	14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
	4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
	11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
	
	12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, //S6.
	10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
	9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
	4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,

	4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, //S7.
	13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
	1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
	6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,

	13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, //S8.
	1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
	7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
	2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};

static const uint8_t ip_table[64]=
{  
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

static const uint8_t inv_ip_table[64]=
{  
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41,  9, 49, 17, 57, 25
};

static const uint8_t pc1_table[56]=
{
	57, 49, 41, 33, 25, 17,  9, //C().
	 1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27,
	19, 11,  3, 60, 52, 44, 36,
	
	63, 55, 47, 39, 31, 23, 15, //D().
	 7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29,
	21, 13,  5, 28, 20, 12,  4
};

static const uint8_t pc2_table[48]=
{
	14, 17, 11, 24,  1,  5,
	 3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8,
	16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

static const uint8_t e_table[48]=
{  
	32,  1,  2,  3,  4,  5,
	 4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32,  1
};

static const uint8_t p_table[32]=
{
	16,  7, 20, 21,  
	29, 12, 28, 17,  
	 1, 15, 23, 26,  
	 5, 18, 31, 10, 
	 2,  8, 24, 14,  
	32, 27,  3,  9, 
	19, 13, 30,  6,  
	22, 11,  4, 25
};

static uint8_t des_key[768]; //16*48.


/* 字节转换位 */
static void byte_to_bits(uint8_t *in, uint8_t *out)
{
	uint8_t i, j, tmp;
	
	for(i=0; i<8; i++)
	{
		tmp = in[i];
		
		for(j=(i+1)*8; j>i*8; j--)
		{
			out[j-1] = tmp & 0x01;
			tmp >>= 1;
		}
	}
}

/* 位转换字节 */
static void bits_to_byte(uint8_t *in, uint8_t *out)
{
	uint8_t i, tmp;
	
	for(i=0; i<8; i++)
	{
		tmp = i * 8;
		out[i] = (in[tmp] << 7)   | (in[tmp+1] << 6) |
				 (in[tmp+2] << 5) | (in[tmp+3] << 4) |
				 (in[tmp+4] << 3) | (in[tmp+5] << 2) |
				 (in[tmp+6] << 1) | in[tmp+7];
	}	
}

/* 异或操作 */
static void byte_xor(uint8_t *in1_out, uint8_t *in2, uint8_t num)
{
	uint8_t i;
	
	for(i=0; i<num; i++)
	{
		in1_out[i] ^= in2[i];
	}	
}

/* 将输入数据用已知表进行置换 */
static void permutation(uint8_t *in, uint8_t *out, const uint8_t *table, uint8_t num)
{
	uint8_t i, tmp;
	
	for(i=0; i<num; i++)
	{
		tmp = table[i] - 1;
		out[i] = in[tmp];
	}	
}

/* 选择置换 */
static void select_permutation(uint8_t *in_out)
{
	uint8_t i, j, tmp;
	uint8_t r, c;
	
	for(i=0; i<8; i++)
	{
		tmp = i * 6;
		r = (in_out[tmp] << 1) + in_out[tmp+5]; //行.
		c = (in_out[tmp+1] << 3) + (in_out[tmp+2] << 2) + (in_out[tmp+3] << 1) + in_out[tmp+4]; //列.
		tmp = (r << 4) + c; //r*16+c.
		tmp = s_table[i][tmp]; //选择置换，把6位输入换成4位输出.
		
		j = i * 4;
		in_out[j+0] = (tmp >> 3) & 0x01; //转换成1位形式.
		in_out[j+1] = (tmp >> 2) & 0x01;
		in_out[j+2] = (tmp >> 1) & 0x01;
		in_out[j+3] = tmp & 0x01;
	}	
}

/* 生成每组key */
static void key_proc(uint8_t *in, uint8_t *out)
{
	uint8_t i, left[2], right[2];
	uint8_t num, left_right[56], tmp[64];
	
	byte_to_bits(in, tmp); //64位按字节存储到tmp，方便后续计算.
	permutation(tmp, left_right, pc1_table, 56); //PC1置换，存到k_tmp.
	
	for(num=0; num<16; num++)
	{
		if(num == 0 || num == 1 || num == 8 || num == 15) //循环左移1位.
		{
			left[0] = left_right[0]; //最左端.
			right[0] = left_right[28];
			for(i=0; i<27; i++)
			{
				left_right[i] = left_right[i+1];
				left_right[i+28] = left_right[i+29];
			}
			left_right[27] = left[0];
			left_right[55] = right[0];
		}
		else //循环左移2位.
		{
			left[0] = left_right[0]; //最左端.
			left[1] = left_right[1];
			right[0] = left_right[28];
			right[1] = left_right[29];
			for(i=0; i<26; i++)
			{
				left_right[i] = left_right[i+2];
				left_right[i+28] = left_right[i+30];
			}
			left_right[26] = left[0];
			left_right[27] = left[1];
			left_right[54] = right[0];
			left_right[55] = right[1];
		}
		
		permutation(left_right, &out[num*48], pc2_table, 48); //PC2置换，生成48字节key.
	}
}

/*
	加解密算法核心(应用层不应调用)
	in_out： 8字节加(解)密数据
	key：	 8字节密钥
	enc_dec：加(解)密标志，ENCRYPT=加密、DECRYPT=解密
*/
void yd_des_crypto(uint8_t *in_out, uint8_t *key, uint8_t enc_dec)
{
	uint8_t i, j;
	uint8_t t, tmp[64], left_right[64];
	
	key_proc(key, des_key); //生成key.
	
	byte_to_bits(in_out, tmp); //64位按字节存储到tmp，方便后续计算.
	permutation(tmp, left_right, ip_table, 64); //初始置换，存到left_right.
	
	for(i=0; i<16; i++)
	{
		permutation(&left_right[32], tmp, e_table, 48); //右半部进行E置换，32位变48位，存到tmp.
		if(enc_dec == DES_ENCRYPT) //加密.
		{
			byte_xor(tmp, &des_key[i*48], 48); //E置换后与K异或，存到tmp.
		}
		else //解密.
		{
			byte_xor(tmp, &des_key[(15-i)*48], 48); //E置换后与K异或，存到tmp.
		}
		select_permutation(tmp); //选择置换，48位变32位，存到tmp左半部.
		permutation(tmp, &tmp[32], p_table, 32); //P置换，存到tmp右半部.
		byte_xor(left_right, &tmp[32], 32); //P置换后与左半部异或.
		if(i != 15) //最后一轮不交换.
		{
			for(j=0; j<32; j++) //左右半部交换，异或后做右半部，以前右半部做左半部.
			{
				t = left_right[j+32];
				left_right[j+32] = left_right[j];
				left_right[j] = t;
			}
		}
	}
	
	permutation(left_right, tmp, inv_ip_table, 64); //P逆置换.
	bits_to_byte(tmp, in_out); //转为字节输出.
}
