
/* Apache License 2.0 */

/*
	文件：yd_sha1.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：SHA1算法实现，详情参考《FIPS PUB 180-4》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#include "yd_sha1.h"


static uint32_t hash_message_length=0, hash_message_length_tmp=0; //要计算消息长度.


/* 统计消息长度 */
static bool count_hash_message_length(uint8_t *message)
{
	uint32_t tmp;
	
	tmp = 0;
	while(message[tmp] != '\0')
	{
		tmp++;
		/* 限制：最大计算(0xffffffff >> 3) = 536870911字节 */
		if(tmp > 536870911)
		{
			return false;
		}
	}
	
	hash_message_length = tmp;
	hash_message_length_tmp = tmp; //消息长度.
	
	return true;
}

/*
	数据填充
	false=数据没有填充完；true=数据填充完成
*/
static bool padding_bits(uint8_t *message, uint8_t *m_8bit)
{
	uint8_t i;
	uint32_t tmp;
	
	if(hash_message_length >= 64)
	{
		for(i=0; i<64; i++)
		{
			m_8bit[i] = message[i];
		}
		
		hash_message_length -= 64;
	}
	else //小于64字节.
	{
		if(hash_message_length >= 56) //56-63字节之间，一个块填充不完，还需要填充1次.
		{
			for(i=0; i<hash_message_length; i++)
			{
				m_8bit[i] = message[i];
			}
			m_8bit[i++] = 0x80;
			while(i < 64)
			{
				m_8bit[i++] = 0;
			}
			
			hash_message_length = 0;
		}
		else //小于等于56字节.
		{
			for(i=0; i<hash_message_length; i++)
			{
				m_8bit[i] = message[i];
			}
			
			/* 消息小于56字节时或者消息是64的倍数时，‘1’没有填充 */
			if(hash_message_length != 0 || hash_message_length_tmp % 64 == 0)
			{
				m_8bit[i++] = 0x80;
			}
			
			while(i < 56)
			{
				m_8bit[i++] = 0;
			}
			
			while(i < 60) //最大计算数据长度限制到32位，所以这4字节填0.
			{
				m_8bit[i++] = 0;
			}
			
			tmp = hash_message_length_tmp * 8;
			m_8bit[60] = tmp >> 24;
			m_8bit[61] = tmp >> 16;
			m_8bit[62] = tmp >> 8;
			m_8bit[63] = tmp;
			
			return true;
		}
	}
	
	return false;
}

/* 准备Wt */
static void prepare_wt(uint8_t *m, uint32_t *w)
{
	uint8_t t, t_tmp;
	uint32_t tmp;
	
	for(t=0; t<16; t++)
	{
		t_tmp = t << 2; //t<<2=t*4.
		w[t] = m[t_tmp]<<24 | m[t_tmp+1]<<16 | m[t_tmp+2]<<8 | m[t_tmp+3]; //大端.
	}
	
	while(t<80) //异或，并循环左移1位.
	{
		w[t] = w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16];
		tmp = w[t] >> 31;
		w[t] <<= 1;
		w[t] |= tmp;
		
		t++;
	}
}

/* 计算值 */
static void compute_hash_value(uint32_t *wt, uint32_t *H)
{
	uint8_t t;
	uint32_t a, b, c, d, e;
	uint32_t T, ft, kt, tmp;
	
	/* 2步------------------------------------------------------------ */
	a = H[0];
	b = H[1];
	c = H[2];
	d = H[3];
	e = H[4];
	
	/* 3步------------------------------------------------------------ */
	for(t=0; t<80; t++)
	{
		if(t < 20)
		{
			kt = 0x5a827999;
			ft = (b & c) ^ (~b & d);
		}
		else if(t < 40)
		{
			kt = 0x6ed9eba1;
			ft = b ^ c ^ d;
		}
		else if(t < 60)
		{
			kt = 0x8f1bbcdc;
			ft = (b & c) ^ (b & d) ^ (c & d);
		}
		else //t<80.
		{
			kt = 0xca62c1d6;
			ft = b ^ c ^ d;
		}
		
		tmp = a << 5;
		tmp |= a >> 27; //a循环左移5位.
		T = tmp + ft + e + kt + wt[t];
		e = d;
		d = c;
		tmp = b << 30;
		tmp |= b >> 2; //b循环左移30位.
		c = tmp;
		b = a;
		a = T;
	}
	
	/* 4步------------------------------------------------------------ */
	H[0] += a;
	H[1] += b;
	H[2] += c;
	H[3] += d;
	H[4] += e;
}

/*
	产生安全散列值SHA1
	message：参与计算的数据
	sha1：	 计算得到的散列值(160位)
*/
bool yd_sha1(uint8_t *message, uint32_t *sha1)
{
	uint8_t flag, m_8bit[64];
	uint32_t i, wt[80], H[5];
	
	if(false == count_hash_message_length(message))
	{
		return false;
	}
	
	H[0] = 0x67452301;
	H[1] = 0xefcdab89;
	H[2] = 0x98badcfe;
	H[3] = 0x10325476;
	H[4] = 0xc3d2e1f0;
	
	flag = 1;
	while(flag == 1)
	{
		/* 0步------------------------------------------------------------ */
		i = hash_message_length_tmp - hash_message_length; //定位要计算的消息.
		if(true == padding_bits(&message[i], m_8bit))
		{
			flag = 0;
		}
		
		/* 1步------------------------------------------------------------ */
		prepare_wt(m_8bit, wt);
		
		/* 2-4步---------------------------------------------------------- */
		compute_hash_value(wt, H);
	}
	
	sha1[0] = H[0];
	sha1[1] = H[1];
	sha1[2] = H[2];
	sha1[3] = H[3];
	sha1[4] = H[4];
	
	return true;
}
