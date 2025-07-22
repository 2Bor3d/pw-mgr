#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHACHA20_IMPLEMENTATION
#include "ChaCha20.h"

int encrypt(uint8_t key[32], uint8_t nonce[12], uint8_t *data)
{
    printf("data: %s\n", data);
    for (int i = 0; i < sizeof(data)/sizeof(uint8_t); i++) {printf("%02x", data[i]);} printf("\n");
    printf("key: ");
    for( int i=0; i<32; ++i ) printf( "%02x", (key)[i] ); printf( "\n" );

    uint32_t count = 0x00000001;
    ChaCha20_Ctx ctx;
    ChaCha20_init(&ctx, key, nonce, count);
   ChaCha20_xor(&ctx, data, strlen(data));

    return 0;
}
