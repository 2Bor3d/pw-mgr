#include "argon2.h"

#define CHACHA20_IMPLEMENTATION

#include "ChaCha20.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define HASHLEN 32
#define SALTLEN 16
#define PWD "password"

int main(void)
{
    key256_t hash;

    uint8_t salt[SALTLEN];
    memset( salt, 0x00, SALTLEN );

    uint8_t *pwd = (uint8_t *)strdup(PWD);
    uint32_t pwdlen = strlen((char *)pwd);

    uint32_t t_cost = 2;            // 2-pass computation
    uint32_t m_cost = (1<<16);      // 64 mebibytes memory usage
    uint32_t parallelism = 1;       // number of threads and lanes

    // high-level API
    argon2i_hash_raw(t_cost, m_cost, parallelism, pwd, pwdlen, salt, SALTLEN, hash, HASHLEN);
    for( int i=0; i<HASHLEN; ++i ) printf( "%02x", hash[i] ); printf( "\n" );

    nonce96_t nonce = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00,
    };

    uint32_t count = 0x00000001;

    uint8_t data[] = {0x61, 0x5e, 0xba, 0x01, 0x33, 0x4e, 0x24};

    ChaCha20_Ctx ctx;
    ChaCha20_init(&ctx, hash, nonce, count);
    ChaCha20_xor(&ctx, data, sizeof(data));
    for( int i=0; i<(sizeof(data)/sizeof(uint8_t)); ++i ) printf( "%02x", data[i] ); printf( "\n" );
    printf("%s\n", data);

    ChaCha20_init(&ctx, hash, nonce, count);
    ChaCha20_xor(&ctx, data, sizeof(data));
    
    printf("%s\n", data);
}
