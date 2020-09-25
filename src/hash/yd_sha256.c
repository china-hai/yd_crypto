
/* Apache License 2.0 */

/*
	文件：yd_sha256.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：SHA256算法实现，详情参考《FIPS PUB 180-4》
	版本：README.md定义
*/

#include "yd_sha256.h"


static uint32_t k_table[64] =
{	/* 下面数据由前64个质数开3次方的前32位小数部分(转二进制，乘2取整)得到 */
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

/*
 *	数据填充
 *	返回值：false=数据没有填充完；true=数据填充完成
 */
static bool padding_bits(uint8_t *msg,
						 uint32_t msg_length,
						 uint32_t *msg_length_remain,
						 uint8_t *m_8bit)
{
	uint8_t i;
	
	if(*msg_length_remain >= 64)
	{
		for(i=0; i<64; i++)
		{
			m_8bit[i] = msg[i];
		}
		
		*msg_length_remain -= 64;
	}
	else //小于64字节.
	{
		if(*msg_length_remain >= 56) //56-63字节之间，一个块填充不完，还需要填充1次.
		{
			for(i=0; i<*msg_length_remain; i++)
			{
				m_8bit[i] = msg[i];
			}
			m_8bit[i++] = 0x80;
			while(i < 64)
			{
				m_8bit[i++] = 0;
			}
			
			*msg_length_remain = 0;
		}
		else //小于等于56字节.
		{
			for(i=0; i<*msg_length_remain; i++)
			{
				m_8bit[i] = msg[i];
			}
			
			/* 消息小于56字节时或者消息是64的倍数时，‘1’没有填充 */
			if(*msg_length_remain != 0 || msg_length % 64 == 0)
			{
				m_8bit[i++] = 0x80;
			}
			
			while(i < 56)
			{
				m_8bit[i++] = 0;
			}
			
			while(i < 60) //最大计算数据长度限制到32位，所以(l=L)的这4字节填0.
			{
				m_8bit[i++] = 0;
			}
			
			msg_length <<= 3; //乘8转为位长度.
			m_8bit[60] = msg_length >> 24;
			m_8bit[61] = msg_length >> 16;
			m_8bit[62] = msg_length >> 8;
			m_8bit[63] = msg_length;
			
			return true;
		}
	}
	
	return false;
}

/* 准备Wt */
static void prepare_wt(uint8_t *m, uint32_t *w)
{
	uint8_t t, t_tmp;
	uint32_t tmp, tmp1, tmp2;
	
	for(t=0; t<16; t++)
	{
		t_tmp = t << 2; //t<<2=t*4.
		w[t] = m[t_tmp]<<24 | m[t_tmp+1]<<16 | m[t_tmp+2]<<8 | m[t_tmp+3]; //大端.
	}
	
	while(t<64)
	{
		tmp1 = w[t-2] << 15;
		tmp2 = w[t-2] >> 17;
		tmp = tmp1 | tmp2; //循环右移17位.
		
		tmp1 = w[t-2] << 13;
		tmp2 = w[t-2] >> 19;
		tmp ^= tmp1 | tmp2; //循环右移19位.
		
		tmp1 = w[t-2] >> 10;
		tmp ^= tmp1; //右移10位.
		
		w[t] = tmp + w[t-7];
		
		tmp1 = w[t-15] << 25;
		tmp2 = w[t-15] >> 7;
		tmp = tmp1 | tmp2; //循环右移7位.
		
		tmp1 = w[t-15] << 14;
		tmp2 = w[t-15] >> 18;
		tmp ^= tmp1 | tmp2; //循环右移18位.
		
		tmp1 = w[t-15] >> 3;
		tmp ^= tmp1; //右移3位.
		
		w[t] += tmp;
		
		w[t] += w[t-16];
		
		t++;
	}
}

/* 计算值 */
static void compute_hash_value(uint32_t *wt, uint32_t *H)
{
	uint8_t t;
	uint32_t a, b, c, d, e, f, g, h;
	uint32_t T1, T2;
	uint32_t tmp, tmp1, tmp2;
	
	/* 2步------------------------------------------------------------ */
	a = H[0];
	b = H[1];
	c = H[2];
	d = H[3];
	e = H[4];
	f = H[5];
	g = H[6];
	h = H[7];
	
	/* 3步------------------------------------------------------------ */
	for(t=0; t<64; t++)
	{
		T1 = h;
		
		tmp1 = e << 26;
		tmp2 = e >> 6;
		tmp = tmp1 | tmp2; //循环右移6位.
		
		tmp1 = e << 21;
		tmp2 = e >> 11;
		tmp ^= tmp1 | tmp2; //循环右移11位.
		
		tmp1 = e << 7;
		tmp2 = e >> 25;
		tmp ^= tmp1 | tmp2; //循环右移25位.
		
		T1 += tmp;
		T1 += (e & f) ^ (~e & g);
		T1 += k_table[t];
		T1 += wt[t];
		
		tmp1 = a << 30;
		tmp2 = a >> 2;
		tmp = tmp1 | tmp2; //循环右移2位.
		
		tmp1 = a << 19;
		tmp2 = a >> 13;
		tmp ^= tmp1 | tmp2; //循环右移13位.
		
		tmp1 = a << 10;
		tmp2 = a >> 22;
		tmp ^= tmp1 | tmp2; //循环右移22位.
		
		T2 = tmp;
		T2 += (a & b) ^ (a & c) ^ (b & c);
		
		h = g;
		g = f;
		f = e;
		e = d + T1;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;
	}
	
	/* 4步------------------------------------------------------------ */
	H[0] += a;
	H[1] += b;
	H[2] += c;
	H[3] += d;
	H[4] += e;
	H[5] += f;
	H[6] += g;
	H[7] += h;
}

/*
 *	产生安全散列值SHA256
 *	msg：		参与计算的数据
 *	msg_length：参与计算的数据长度
 *	sha256： 	计算得到的散列值(256位)
 */
bool yd_sha256(uint8_t *msg, uint32_t msg_length, uint32_t *sha256)
{
	uint8_t flag, m_8bit[64];
	uint32_t i, msg_length_remain;
	uint32_t wt[64], H[8];
	
	/* 限制：最大计算0xffffffff / 8 = 536870911字节 */
	if(msg_length > 536870911)
	{
		return false;
	}
	msg_length_remain = msg_length;
	
	H[0] = 0x6a09e667;
	H[1] = 0xbb67ae85;
	H[2] = 0x3c6ef372;
	H[3] = 0xa54ff53a;
	H[4] = 0x510e527f;
	H[5] = 0x9b05688c;
	H[6] = 0x1f83d9ab;
	H[7] = 0x5be0cd19;
	
	flag = 1;
	do
	{
		/* 0步------------------------------------------------------------ */
		i = msg_length - msg_length_remain; //定位要计算的消息.
		if(true == padding_bits(&msg[i],
								msg_length,
								&msg_length_remain,
								m_8bit))
		{
			flag = 0;
		}
		
		/* 1步------------------------------------------------------------ */
		prepare_wt(m_8bit, wt);
		
		/* 2-4步------------------------------------------------------------ */
		compute_hash_value(wt, H);
	}while(flag == 1);
	
	sha256[0] = H[0];
	sha256[1] = H[1];
	sha256[2] = H[2];
	sha256[3] = H[3];
	sha256[4] = H[4];
	sha256[5] = H[5];
	sha256[6] = H[6];
	sha256[7] = H[7];
	
	return true;
}
