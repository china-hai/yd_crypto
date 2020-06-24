
/* 免费，无许可 */

/*
	文件：yd_md5.c
	作者：wzh
	邮箱：wangzhihai_138@163.com
	简介：MD5算法实现，详情参考《RFC 1321》
	版本：V1.0.01
*/

/*
	2020-4-11：第一次发布.
*/

#include "yd_md5.h"


static uint32_t md5_message_length=0, md5_message_length_tmp=0; //要计算消息长度.
static uint32_t t_table[64] =
{	/* 下面值由4294967296*abs(sin(i))得到，i=1~64，i是弧度，4294967296=0xffffffff+1 */
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};


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
	
	md5_message_length = tmp;
	md5_message_length_tmp = tmp; //消息长度.
	
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
	
	if(md5_message_length >= 64)
	{
		for(i=0; i<64; i++)
		{
			m_8bit[i] = message[i];
		}
		
		md5_message_length -= 64;
	}
	else //小于64字节.
	{
		if(md5_message_length >= 56) //56-63字节之间，一个块填充不完，还需要填充1次.
		{
			for(i=0; i<md5_message_length; i++)
			{
				m_8bit[i] = message[i];
			}
			m_8bit[i++] = 0x80;
			while(i < 64)
			{
				m_8bit[i++] = 0;
			}
			
			md5_message_length = 0;
		}
		else //小于等于56字节.
		{
			for(i=0; i<md5_message_length; i++)
			{
				m_8bit[i] = message[i];
			}
			
			/* 消息小于56字节时或者消息是64的倍数时，‘1’没有填充 */
			if(md5_message_length != 0 || md5_message_length_tmp % 64 == 0)
			{
				m_8bit[i++] = 0x80;
			}
			
			while(i < 56)
			{
				m_8bit[i++] = 0;
			}
			
			tmp = md5_message_length_tmp * 8;
			m_8bit[56] = tmp;
			m_8bit[57] = tmp >> 8;
			m_8bit[58] = tmp >> 16;
			m_8bit[59] = tmp >> 24;
			
			i = 60;
			while(i < 64) //最大计算数据长度限制到32位，所以这4字节填0.
			{
				m_8bit[i++] = 0;
			}
			
			return true;
		}
	}
	
	return false;
}

static void compute_func(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d,
						 uint32_t X, uint32_t T, uint8_t S, uint8_t flag)
{
	uint32_t a_tmp, b_tmp, c_tmp, d_tmp;
	uint32_t tmp, tmp1, tmp2;
	
	a_tmp = *a;
	b_tmp = *b;
	c_tmp = *c;
	d_tmp = *d;
	
	if(flag == 'F') //F(x,y,z)=(x&y)|(~x&z).
	{
		tmp = (b_tmp & c_tmp) | (~b_tmp & d_tmp);
	}
	else if(flag == 'G') //G(x,y,z)=(x&z)|(y&~x).
	{
		tmp = (b_tmp & d_tmp) | (c_tmp & ~d_tmp);
	}
	else if(flag == 'H') //H(x,y,z)=x^y^z.
	{
		tmp = b_tmp ^ c_tmp ^ d_tmp;
	}
	else if(flag == 'I') //I(x,y,z)=y^(x|~z).
	{
		tmp = c_tmp ^ (b_tmp | ~d_tmp);
	}
	else
	{}
	
	tmp += a_tmp + X + T;
	tmp1 = tmp >> (32 - S);
	tmp2 = tmp << S;
	tmp = tmp1 | tmp2; //循环左移S位.
	
	a_tmp = b_tmp + tmp;
	
	*a = a_tmp;
	*b = b_tmp;
	*c = c_tmp;
	*d = d_tmp;
}

/* 计算值 */
static void compute_md5_value(uint32_t *X, uint32_t *abcd)
{
	uint32_t a, b, c, d;
	
	a = abcd[0];
	b = abcd[1];
	c = abcd[2];
	d = abcd[3];
	
	/* Round 1, a=b+((a+F(b,c,d)+X[k]+T[i])循环左移S位) */
	compute_func(&a, &b, &c, &d, X[0], t_table[0], 7, 'F');
	compute_func(&d, &a, &b, &c, X[1], t_table[1], 12, 'F');
	compute_func(&c, &d, &a, &b, X[2], t_table[2], 17, 'F');
	compute_func(&b, &c, &d, &a, X[3], t_table[3], 22, 'F');
	compute_func(&a, &b, &c, &d, X[4], t_table[4], 7, 'F');
	compute_func(&d, &a, &b, &c, X[5], t_table[5], 12, 'F');
	compute_func(&c, &d, &a, &b, X[6], t_table[6], 17, 'F');
	compute_func(&b, &c, &d, &a, X[7], t_table[7], 22, 'F');
	compute_func(&a, &b, &c, &d, X[8], t_table[8], 7, 'F');
	compute_func(&d, &a, &b, &c, X[9], t_table[9], 12, 'F');
	compute_func(&c, &d, &a, &b, X[10], t_table[10], 17, 'F');
	compute_func(&b, &c, &d, &a, X[11], t_table[11], 22, 'F');
	compute_func(&a, &b, &c, &d, X[12], t_table[12], 7, 'F');
	compute_func(&d, &a, &b, &c, X[13], t_table[13], 12, 'F');
	compute_func(&c, &d, &a, &b, X[14], t_table[14], 17, 'F');
	compute_func(&b, &c, &d, &a, X[15], t_table[15], 22, 'F');
	
	/* Round 2, a=b+((a+G(b,c,d)+X[k]+T[i])循环左移S位) */
	compute_func(&a, &b, &c, &d, X[1], t_table[16], 5, 'G');
	compute_func(&d, &a, &b, &c, X[6], t_table[17], 9, 'G');
	compute_func(&c, &d, &a, &b, X[11], t_table[18], 14, 'G');
	compute_func(&b, &c, &d, &a, X[0], t_table[19], 20, 'G');
	compute_func(&a, &b, &c, &d, X[5], t_table[20], 5, 'G');
	compute_func(&d, &a, &b, &c, X[10], t_table[21], 9, 'G');
	compute_func(&c, &d, &a, &b, X[15], t_table[22], 14, 'G');
	compute_func(&b, &c, &d, &a, X[4], t_table[23], 20, 'G');
	compute_func(&a, &b, &c, &d, X[9], t_table[24], 5, 'G');
	compute_func(&d, &a, &b, &c, X[14], t_table[25], 9, 'G');
	compute_func(&c, &d, &a, &b, X[3], t_table[26], 14, 'G');
	compute_func(&b, &c, &d, &a, X[8], t_table[27], 20, 'G');
	compute_func(&a, &b, &c, &d, X[13], t_table[28], 5, 'G');
	compute_func(&d, &a, &b, &c, X[2], t_table[29], 9, 'G');
	compute_func(&c, &d, &a, &b, X[7], t_table[30], 14, 'G');
	compute_func(&b, &c, &d, &a, X[12], t_table[31], 20, 'G');
	
	/* Round 3, a=b+((a+H(b,c,d)+X[k]+T[i])循环左移S位) */
	compute_func(&a, &b, &c, &d, X[5], t_table[32], 4, 'H');
	compute_func(&d, &a, &b, &c, X[8], t_table[33], 11, 'H');
	compute_func(&c, &d, &a, &b, X[11], t_table[34], 16, 'H');
	compute_func(&b, &c, &d, &a, X[14], t_table[35], 23, 'H');
	compute_func(&a, &b, &c, &d, X[1], t_table[36], 4, 'H');
	compute_func(&d, &a, &b, &c, X[4], t_table[37], 11, 'H');
	compute_func(&c, &d, &a, &b, X[7], t_table[38], 16, 'H');
	compute_func(&b, &c, &d, &a, X[10], t_table[39], 23, 'H');
	compute_func(&a, &b, &c, &d, X[13], t_table[40], 4, 'H');
	compute_func(&d, &a, &b, &c, X[0], t_table[41], 11, 'H');
	compute_func(&c, &d, &a, &b, X[3], t_table[42], 16, 'H');
	compute_func(&b, &c, &d, &a, X[6], t_table[43], 23, 'H');
	compute_func(&a, &b, &c, &d, X[9], t_table[44], 4, 'H');
	compute_func(&d, &a, &b, &c, X[12], t_table[45], 11, 'H');
	compute_func(&c, &d, &a, &b, X[15], t_table[46], 16, 'H');
	compute_func(&b, &c, &d, &a, X[2], t_table[47], 23, 'H');
	
	/* Round 4, a=b+((a+I(b,c,d)+X[k]+T[i])循环左移S位) */
	compute_func(&a, &b, &c, &d, X[0], t_table[48], 6, 'I');
	compute_func(&d, &a, &b, &c, X[7], t_table[49], 10, 'I');
	compute_func(&c, &d, &a, &b, X[14], t_table[50], 15, 'I');
	compute_func(&b, &c, &d, &a, X[5], t_table[51], 21, 'I');
	compute_func(&a, &b, &c, &d, X[12], t_table[52], 6, 'I');
	compute_func(&d, &a, &b, &c, X[3], t_table[53], 10, 'I');
	compute_func(&c, &d, &a, &b, X[10], t_table[54], 15, 'I');
	compute_func(&b, &c, &d, &a, X[1], t_table[55], 21, 'I');
	compute_func(&a, &b, &c, &d, X[8], t_table[56], 6, 'I');
	compute_func(&d, &a, &b, &c, X[15], t_table[57], 10, 'I');
	compute_func(&c, &d, &a, &b, X[6], t_table[58], 15, 'I');
	compute_func(&b, &c, &d, &a, X[13], t_table[59], 21, 'I');
	compute_func(&a, &b, &c, &d, X[4], t_table[60], 6, 'I');
	compute_func(&d, &a, &b, &c, X[11], t_table[61], 10, 'I');
	compute_func(&c, &d, &a, &b, X[2], t_table[62], 15, 'I');
	compute_func(&b, &c, &d, &a, X[9], t_table[63], 21, 'I');
	
	abcd[0] += a;
	abcd[1] += b;
	abcd[2] += c;
	abcd[3] += d;
}

/*
	产生MD5
	message：参与计算的数据(字符串)
	md5：	 计算得到的值(128位)
*/
bool yd_md5(uint8_t *message, uint8_t *md5)
{
	uint8_t k, k_tmp, flag, m_8bit[64];
	uint32_t i, X[16], abcd[4];
	
	if(false == count_hash_message_length(message)) //字符串长度统计.
	{
		return false;
	}
	
	abcd[0] = 0x67452301; //初始化MD缓冲器.
	abcd[1] = 0xefcdab89;
	abcd[2] = 0x98badcfe;
	abcd[3] = 0x10325476;
	
	flag = 1;
	while(flag == 1)
	{
		i = md5_message_length_tmp - md5_message_length; //定位要计算的消息.
		if(true == padding_bits(&message[i], m_8bit))
		{
			flag = 0; //完成最后填充，结束循环.
		}
		
		for(k=0; k<16; k++)
		{
			k_tmp = k << 2; //k<<2=k*4.
			X[k] = m_8bit[k_tmp+3]<<24 | m_8bit[k_tmp+2]<<16 | m_8bit[k_tmp+1]<<8 | m_8bit[k_tmp];
		}
		
		compute_md5_value(X, abcd);
	}
	
	/* 显示转换 */
	md5[0] = abcd[0];
	md5[1] = abcd[0] >> 8;
	md5[2] = abcd[0] >> 16;
	md5[3] = abcd[0] >> 24;
	
	md5[4] = abcd[1];
	md5[5] = abcd[1] >> 8;
	md5[6] = abcd[1] >> 16;
	md5[7] = abcd[1] >> 24;
	
	md5[8] = abcd[2];
	md5[9] = abcd[2] >> 8;
	md5[10] = abcd[2] >> 16;
	md5[11] = abcd[2] >> 24;
	
	md5[12] = abcd[3];
	md5[13] = abcd[3] >> 8;
	md5[14] = abcd[3] >> 16;
	md5[15] = abcd[3] >> 24;
	
	return true;
}
