
#include "demo.h"
#include "yd_sha1.h"
#include "yd_sha224.h"
#include "yd_sha256.h"


static uint8_t str1[]="abc";
static uint8_t str2[]="abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";


/* SHA1 */
void sha1_demo(void)
{
	uint32_t s1[5], s2[5];
	
	yd_sha1(str1, 3, s1);
	yd_sha1(str2, 56, s2);
}

/* SHA224 */
void sha224_demo(void)
{
	uint32_t s1[7], s2[7];
	
	yd_sha224(str1, 3, s1);
	yd_sha224(str2, 56, s2);
}

/* SHA256 */
void sha256_demo(void)
{
	uint32_t s1[8], s2[8];
	
	yd_sha256(str1, 3, s1);
	yd_sha256(str2, 56, s2);
}
