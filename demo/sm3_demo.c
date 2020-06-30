
#include "demo.h"
#include "yd_sm3.h"


void sm3_demo(void)
{
	uint8_t str1[]="abc";
	uint8_t str2[]="abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";
	uint32_t sm3_1[8], sm3_2[8];
	
	yd_sm3(str1, sm3_1);
	yd_sm3(str2, sm3_2);
}
