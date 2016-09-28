#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "crypto/sha2.h"
#include "common/utils.h"

/*
See http://www.di-mgt.com.au/sha_testvectors.html
*/
int main()
{
	SHA384_CTX ctx;
	uint8_t res[SHA384_DIGEST_LENGTH];
	char strres[SHA384_DIGEST_STRING_LENGTH];
	char* vectors[] = {
		"38B060A751AC96384CD9327EB1B1E36A21FDB71114BE07434C0CC7BF63F6E1DA274EDEBFE76F65FBD51AD2F14898B95B",
		"",

		"54A59B9F22B0B80880D8427E548B7C23ABD873486E1F035DCE9CD697E85175033CAA88E6D57BC35EFAE0B5AFD3145F31",
		"a",

		"CB00753F45A35E8BB5A03D699AC65007272C32AB0EDED1631A8B605A43FF5BED8086072BA1E7CC2358BAECA134C825A7",
		"abc",

		"473ED35167EC1F5D8E550368A3DB39BE54639F828868E9454C239FC8B52E3C61DBD0D8B4DE1390C256DCBB5D5FD99CD5",
		"message digest",

		"FEB67349DF3DB6F5924815D6C3DC133F091809213731FE5C7B5F4999E463479FF2877F5F2936FA63BB43784B12F3EBB4",
		"abcdefghijklmnopqrstuvwxyz",

		"3391FDDDFC8DC7393707A65B1B4709397CF8B1D162AF05ABFE8F450DE5F36BC6B0455A8520BC4E6F5FE95B1FE3C8452B",
		"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",

		"1761336E3F7CBFE51DEB137F026F89E01A448E3B1FAFA64039C1464EE8732F11A5341A6F41E0C202294736ED64DB1A84",
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",

		"B12932B0627D1C060942F5447764155655BD4DA0C9AFA6DD9B9EF53129AF1B8FB0195996D2DE9CA0DF9D821FFEE67026",
		"12345678901234567890123456789012345678901234567890123456789012345678901234567890",

		"9D0E1809716474CB086E834E310A4A1CED149E9C00F248527972CEC5704C2A5B07B8B3DC38ECC4EBAE97DDD87F3D8985",
		 NULL
	};
	char a10[] = "aaaaaaaaaa";
	int j, i = 0;

	while(vectors[i+1] != NULL)
	{
		SHA384_Init(&ctx);
		SHA384_Update(&ctx, (uint8_t*)vectors[i+1], strlen(vectors[i+1]));
		SHA384_Final(res, &ctx);
		bytesToHex(res, SHA384_DIGEST_LENGTH, strres);
		printf("Vector %i, result = %s, expected = %s\n", i / 2, strres, vectors[i]);
		assert(strcmp(strres, vectors[i]) == 0);
		i += 2;
	}

	// Vector 8, 1 million times "a"
	SHA384_Init(&ctx);
	for(j = 0; j < 1000000 / (sizeof(a10)-1); j++)
	{
		SHA384_Update(&ctx, (uint8_t*)a10, sizeof(a10)-1);
	}
	SHA384_Final(res, &ctx);
	bytesToHex(res, SHA384_DIGEST_LENGTH, strres);
	printf("Vector %i, result = %s, expected = %s\n", i / 2, strres, vectors[i]);
	assert(strcmp(strres, vectors[i]) == 0);

	return 0;
}
