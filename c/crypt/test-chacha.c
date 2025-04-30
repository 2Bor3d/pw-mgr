#include <stdint.h>
#include <stdio.h>
#define CHACHA20_IMPLEMENTATION
#include "ChaCha20.h"

int main()
{
    /*
	key256_t key = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	};

	nonce96_t nonce = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a,
		0x00, 0x00, 0x00, 0x00,
	};
    */
    uint8_t key[32] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    uint8_t nonce[12] = "aaaaaaaaaaaa";

	uint32_t count = 0x00000001;


    uint8_t data[256] = "hello world";

	ChaCha20_Ctx ctx;
	ChaCha20_init(&ctx, key, nonce, count);
	ChaCha20_xor(&ctx, data, sizeof(data));

    printf("%i\n", count);
    count = 0x00000001;
    printf("%s\n", data);

    
    ChaCha20_Ctx ctxx;
	ChaCha20_init(&ctxx, key, nonce, count);
	ChaCha20_xor(&ctxx, data, sizeof(data));
    printf("%i\n", count);
	// The array 'data' is now encrypted (or decrypted if it
	// was already encrypted)
    printf("%s\n", data);
}
