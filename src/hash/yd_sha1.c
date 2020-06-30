
/* Apache License 2.0 */

/*
	�ļ���yd_sha1.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺SHA1�㷨ʵ�֣�����ο���FIPS PUB 180-4��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_sha1.h"


static uint32_t hash_message_length=0, hash_message_length_tmp=0; //Ҫ������Ϣ����.


/* ͳ����Ϣ���� */
static bool count_hash_message_length(uint8_t *message)
{
	uint32_t tmp;
	
	tmp = 0;
	while(message[tmp] != '\0')
	{
		tmp++;
		/* ���ƣ�������(0xffffffff >> 3) = 536870911�ֽ� */
		if(tmp > 536870911)
		{
			return false;
		}
	}
	
	hash_message_length = tmp;
	hash_message_length_tmp = tmp; //��Ϣ����.
	
	return true;
}

/*
	�������
	false=����û������ꣻtrue=����������
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
	else //С��64�ֽ�.
	{
		if(hash_message_length >= 56) //56-63�ֽ�֮�䣬һ������䲻�꣬����Ҫ���1��.
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
		else //С�ڵ���56�ֽ�.
		{
			for(i=0; i<hash_message_length; i++)
			{
				m_8bit[i] = message[i];
			}
			
			/* ��ϢС��56�ֽ�ʱ������Ϣ��64�ı���ʱ����1��û����� */
			if(hash_message_length != 0 || hash_message_length_tmp % 64 == 0)
			{
				m_8bit[i++] = 0x80;
			}
			
			while(i < 56)
			{
				m_8bit[i++] = 0;
			}
			
			while(i < 60) //���������ݳ������Ƶ�32λ��������4�ֽ���0.
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

/* ׼��Wt */
static void prepare_wt(uint8_t *m, uint32_t *w)
{
	uint8_t t, t_tmp;
	uint32_t tmp;
	
	for(t=0; t<16; t++)
	{
		t_tmp = t << 2; //t<<2=t*4.
		w[t] = m[t_tmp]<<24 | m[t_tmp+1]<<16 | m[t_tmp+2]<<8 | m[t_tmp+3]; //���.
	}
	
	while(t<80) //��򣬲�ѭ������1λ.
	{
		w[t] = w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16];
		tmp = w[t] >> 31;
		w[t] <<= 1;
		w[t] |= tmp;
		
		t++;
	}
}

/* ����ֵ */
static void compute_hash_value(uint32_t *wt, uint32_t *H)
{
	uint8_t t;
	uint32_t a, b, c, d, e;
	uint32_t T, ft, kt, tmp;
	
	/* 2��------------------------------------------------------------ */
	a = H[0];
	b = H[1];
	c = H[2];
	d = H[3];
	e = H[4];
	
	/* 3��------------------------------------------------------------ */
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
		tmp |= a >> 27; //aѭ������5λ.
		T = tmp + ft + e + kt + wt[t];
		e = d;
		d = c;
		tmp = b << 30;
		tmp |= b >> 2; //bѭ������30λ.
		c = tmp;
		b = a;
		a = T;
	}
	
	/* 4��------------------------------------------------------------ */
	H[0] += a;
	H[1] += b;
	H[2] += c;
	H[3] += d;
	H[4] += e;
}

/*
	������ȫɢ��ֵSHA1
	message��������������
	sha1��	 ����õ���ɢ��ֵ(160λ)
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
		/* 0��------------------------------------------------------------ */
		i = hash_message_length_tmp - hash_message_length; //��λҪ�������Ϣ.
		if(true == padding_bits(&message[i], m_8bit))
		{
			flag = 0;
		}
		
		/* 1��------------------------------------------------------------ */
		prepare_wt(m_8bit, wt);
		
		/* 2-4��---------------------------------------------------------- */
		compute_hash_value(wt, H);
	}
	
	sha1[0] = H[0];
	sha1[1] = H[1];
	sha1[2] = H[2];
	sha1[3] = H[3];
	sha1[4] = H[4];
	
	return true;
}
