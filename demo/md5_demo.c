
#include "demo.h"
#include "yd_md5.h"


void md5_demo(void)
{
	uint8_t str1[]="";
	uint8_t str2[]="message digest";
	uint8_t str3[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	uint8_t str4[]="12345678901234567890123456789012345678901234567890123456789012345678901234567890";
	uint8_t md5[16];
	
	yd_md5(str1, md5); //空.
	
	yd_md5(str2, md5); //14字符.
	
	yd_md5(str3, md5); //62字符.
	
	yd_md5(str4, md5); //80字符.
}
