
/* Apache License 2.0 */

/*
	�ļ���yd_sha224.c
	���ߣ�wzh
	���䣺wangzhihai_138@163.com
	��飺SHA224�㷨ʵ�֣�����ο���FIPS PUB 180-4��
	�汾��V1.0.01
*/

/*
	2020-4-11����һ�η���.
*/

#include "yd_sha224.h"


static uint32_t hash_message_length=0, hash_message_length_tmp=0; //Ҫ������Ϣ����.
static uint32_t k_table[64] =
{	/* ����������ǰ64��������3�η���ǰ32λС������(ת�����ƣ���2ȡ��)�õ� */
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};


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
			
			while(i < 60) //���������ݳ������Ƶ�32λ������(l=L)����4�ֽ���0.
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
	uint32_t tmp, tmp1, tmp2;
	
	for(t=0; t<16; t++)
	{
		t_tmp = t << 2; //t<<2=t*4.
		w[t] = m[t_tmp]<<24 | m[t_tmp+1]<<16 | m[t_tmp+2]<<8 | m[t_tmp+3]; //���.
	}
	
	while(t<64)
	{
		tmp1 = w[t-2] << 15;
		tmp2 = w[t-2] >> 17;
		tmp = tmp1 | tmp2; //ѭ������17λ.
		
		tmp1 = w[t-2] << 13;
		tmp2 = w[t-2] >> 19;
		tmp ^= tmp1 | tmp2; //ѭ������19λ.
		
		tmp1 = w[t-2] >> 10;
		tmp ^= tmp1; //����10λ.
		
		w[t] = tmp + w[t-7];
		
		tmp1 = w[t-15] << 25;
		tmp2 = w[t-15] >> 7;
		tmp = tmp1 | tmp2; //ѭ������7λ.
		
		tmp1 = w[t-15] << 14;
		tmp2 = w[t-15] >> 18;
		tmp ^= tmp1 | tmp2; //ѭ������18λ.
		
		tmp1 = w[t-15] >> 3;
		tmp ^= tmp1; //����3λ.
		
		w[t] += tmp;
		
		w[t] += w[t-16];
		
		t++;
	}
}

/* ����ֵ */
static void compute_hash_value(uint32_t *wt, uint32_t *H)
{
	uint8_t t;
	uint32_t a, b, c, d, e, f, g, h;
	uint32_t T1, T2;
	uint32_t tmp, tmp1, tmp2;
	
	/* 2��------------------------------------------------------------ */
	a = H[0];
	b = H[1];
	c = H[2];
	d = H[3];
	e = H[4];
	f = H[5];
	g = H[6];
	h = H[7];
	
	/* 3��------------------------------------------------------------ */
	for(t=0; t<64; t++)
	{
		T1 = h;
		
		tmp1 = e << 26;
		tmp2 = e >> 6;
		tmp = tmp1 | tmp2; //ѭ������6λ.
		
		tmp1 = e << 21;
		tmp2 = e >> 11;
		tmp ^= tmp1 | tmp2; //ѭ������11λ.
		
		tmp1 = e << 7;
		tmp2 = e >> 25;
		tmp ^= tmp1 | tmp2; //ѭ������25λ.
		
		T1 += tmp;
		T1 += (e & f) ^ (~e & g);
		T1 += k_table[t];
		T1 += wt[t];
		
		tmp1 = a << 30;
		tmp2 = a >> 2;
		tmp = tmp1 | tmp2; //ѭ������2λ.
		
		tmp1 = a << 19;
		tmp2 = a >> 13;
		tmp ^= tmp1 | tmp2; //ѭ������13λ.
		
		tmp1 = a << 10;
		tmp2 = a >> 22;
		tmp ^= tmp1 | tmp2; //ѭ������22λ.
		
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
	
	/* 4��------------------------------------------------------------ */
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
	������ȫɢ��ֵSHA224
	message��������������
	sha224�� ����õ���ɢ��ֵ(224λ)
*/
bool yd_sha224(uint8_t *message, uint32_t *sha224)
{
	uint8_t flag, m_8bit[64];
	uint32_t i, wt[64], H[8];
	
	if(false == count_hash_message_length(message))
	{
		return false;
	}
	
	H[0] = 0xc1059ed8;
	H[1] = 0x367cd507;
	H[2] = 0x3070dd17;
	H[3] = 0xf70e5939;
	H[4] = 0xffc00b31;
	H[5] = 0x68581511;
	H[6] = 0x64f98fa7;
	H[7] = 0xbefa4fa4;
	
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
		
		/* 2-4��------------------------------------------------------------ */
		compute_hash_value(wt, H);
	}
	
	sha224[0] = H[0];
	sha224[1] = H[1];
	sha224[2] = H[2];
	sha224[3] = H[3];
	sha224[4] = H[4];
	sha224[5] = H[5];
	sha224[6] = H[6];
	
	return true;
}
