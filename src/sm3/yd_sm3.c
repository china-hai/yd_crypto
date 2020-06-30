
/* Apache License 2.0 */

/*
	文件：yd_sm3.h
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：SM3算法实现，详情参考《SM3 GM/T 0004-2012》
	版本：V1.0.01
*/

/*
	2020-6-29：第一次发布.
*/

#include "yd_sm3.h"

static uint32_t sm3_message_length=0, sm3_message_length_tmp=0; //要计算消息长度.


/* 统计消息长度 */
static bool count_sm3_message_length(uint8_t *message)
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
	
	sm3_message_length = tmp;
	sm3_message_length_tmp = tmp; //消息长度.
	
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
	
	if(sm3_message_length >= 64)
	{
		for(i=0; i<64; i++)
		{
			m_8bit[i] = message[i];
		}
		
		sm3_message_length -= 64;
	}
	else //小于64字节.
	{
		if(sm3_message_length >= 56) //56-63字节之间，一个块填充不完，还需要填充1次.
		{
			for(i=0; i<sm3_message_length; i++)
			{
				m_8bit[i] = message[i];
			}
			m_8bit[i++] = 0x80;
			while(i < 64)
			{
				m_8bit[i++] = 0;
			}
			
			sm3_message_length = 0;
		}
		else //小于等于56字节.
		{
			for(i=0; i<sm3_message_length; i++)
			{
				m_8bit[i] = message[i];
			}
			
			/* 消息小于56字节时或者消息是64的倍数时，‘1’没有填充 */
			if(sm3_message_length != 0 || sm3_message_length_tmp % 64 == 0)
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
			
			tmp = sm3_message_length_tmp * 8;
			m_8bit[60] = tmp >> 24;
			m_8bit[61] = tmp >> 16;
			m_8bit[62] = tmp >> 8;
			m_8bit[63] = tmp;
			
			return true;
		}
	}
	
	return false;
}

/* 消息扩展W */
static void prepare_w(uint8_t *m_8bit, uint32_t *w, uint32_t *wt)
{
	uint8_t j, j_tmp;
	uint32_t x, tmp, tmp1, tmp2;
	
	for(j=0; j<16; j++) //w0-15
	{
		j_tmp = j << 2; //j<<2=j*4.
		w[j] = m_8bit[j_tmp]<<24 |
			   m_8bit[j_tmp+1]<<16 |
			   m_8bit[j_tmp+2]<<8 |
			   m_8bit[j_tmp+3]; //大端.
	}
	
	while(j <= 67) //w16-67
	{
		x = w[j-16] ^ w[j-9];
		tmp1 = w[j-3] << 15;
		tmp2 = w[j-3] >> 17;
		tmp = tmp1 | tmp2; //循环左移15位.
		x ^= tmp;
		
		/* P1置换函数 */
		tmp1 = x << 15;
		tmp2 = x >> 17;
		tmp = tmp1 | tmp2; //循环左移15位.
		tmp1 = x << 23;
		tmp2 = x >> 9;
		tmp ^= tmp1 | tmp2; //循环左移23位.
		x ^= tmp;
		
		tmp1 = w[j-13] << 7;
		tmp2 = w[j-13] >> 25;
		tmp = tmp1 | tmp2; //循环左移7位.
		x ^= tmp;
		
		w[j] = x ^ w[j-6];
		j++;
	}
	
	for(j=0; j<=63; j++) //w'0-63
	{
		wt[j] = w[j] ^ w[j+4];
	}
}

/* 计算值 */
static void compute_sm3_value(uint32_t *w, uint32_t *wt, uint32_t *V)
{
	uint8_t j;
	uint32_t a, b, c, d, e, f, g, h;
	uint32_t t, ss1, ss2, tt1, tt2;
	uint32_t tmp, tmp1, tmp2;
	
	a = V[0];
	b = V[1];
	c = V[2];
	d = V[3];
	e = V[4];
	f = V[5];
	g = V[6];
	h = V[7]; //初始向量.
	
	for(j=0; j<64; j++)
	{
		tmp1 = a << 12;
		tmp2 = a >> 20;
		tmp = tmp1 | tmp2; //循环左移12位.
		tmp += e;
		/* T常量 */
		if(j < 16)
		{
			t = 0x79cc4519;
		}
		else
		{
			t = 0x7a879d8a;
		}
		if(j < 32)
		{
			tmp1 = t << j;
			tmp2 = t >> (32-j);
		}
		else
		{
			tmp1 = t << (j-32);
			tmp2 = t >> (64-j);
		}
		tmp += tmp1 | tmp2; //循环左移j位.
		tmp1 = tmp << 7;
		tmp2 = tmp >> 25;
		ss1 = tmp1 | tmp2; //循环左移7位.
		
		tmp1 = a << 12;
		tmp2 = a >> 20;
		tmp = tmp1 | tmp2; //循环左移12位.
		ss2 = ss1 ^ tmp;
		
		/* FF,GG布尔函数 */
		if(j < 16)
		{
			tt1 = a ^ b ^c;
			tt2 = e ^ f ^ g;
		}
		else
		{
			tt1 = (a & b) | (a & c) | (b & c);
			tt2 = (e & f) | (~e & g);
		}
		tt1 += d + ss2 + wt[j];
		tt2 += h + ss1 + w[j];
		
		d = c;
		tmp1 = b << 9;
		tmp2 = b >> 23;
		c = tmp1 | tmp2; //循环左移9位.
		b = a;
		a = tt1;
		h = g;
		tmp1 = f << 19;
		tmp2 = f >> 13;
		g = tmp1 | tmp2;
		f = e;
		/* P0置换函数 */
		tmp1 = tt2 << 9;
		tmp2 = tt2 >> 23; //循环左移9位.
		tmp = tmp1 | tmp2;
		tmp1 = tt2 << 17;
		tmp2 = tt2 >> 15; //循环左移17位.
		tmp ^= tmp1 | tmp2;
		e = tt2 ^ tmp;
	}
	
	V[0] ^= a;
	V[1] ^= b;
	V[2] ^= c;
	V[3] ^= d;
	V[4] ^= e;
	V[5] ^= f;
	V[6] ^= g;
	V[7] ^= h;
}

/*
	产生SM3杂凑值(密码)
	message：参与计算的数据
	sm3： 计算得到的杂凑值(256位)
*/
bool yd_sm3(uint8_t *message, uint32_t *sm3)
{
	uint8_t flag, m_8bit[64];
	uint32_t i, w[68], wt[64], V[8];
	
	if(false == count_sm3_message_length(message))
	{
		return false;
	}
	
	V[0] = 0x7380166f;
	V[1] = 0x4914b2b9;
	V[2] = 0x172442d7;
	V[3] = 0xda8a0600;
	V[4] = 0xa96f30bc;
	V[5] = 0x163138aa;
	V[6] = 0xe38dee4d;
	V[7] = 0xb0fb0e4e; //初始向量值.
	
	flag = 1;
	while(flag == 1)
	{
		i = sm3_message_length_tmp - sm3_message_length; //定位要计算的消息.
		if(true == padding_bits(&message[i], m_8bit))
		{
			flag = 0;
		}
		
		prepare_w(m_8bit, w, wt);
		
		compute_sm3_value(w, wt, V);
	}
	
	sm3[0] = V[0];
	sm3[1] = V[1];
	sm3[2] = V[2];
	sm3[3] = V[3];
	sm3[4] = V[4];
	sm3[5] = V[5];
	sm3[6] = V[6];
	sm3[7] = V[7];
	
	return true;
}
