#include <stdint.h>
#include <stdio.h>

#define CHACHA20_IMPLEMENTATION
#include "ChaCha20.h"

int encrypt(uint8_t key[32], uint8_t nonce[12], uint8_t *data)
{
    printf("%s\n", data);
    uint32_t count = 0x00000001;
    ChaCha20_Ctx ctx;
    ChaCha20_init(&ctx, key, nonce, count);
    ChaCha20_xor(&ctx, data, sizeof(data));

    return 0;
}
