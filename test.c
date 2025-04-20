#include "argon2.h"
#include <stdio.h>
#include <string.h>

#define HASHLEN 32
#define SALTLEN 16
#define PWD "password"

int main(void)
{
    uint8_t hash[HASHLEN];

    uint8_t salt[SALTLEN];
    memset( salt, 0x00, SALTLEN );

    uint8_t *pwd = (uint8_t *)strdup(PWD);
    uint32_t pwdlen = strlen((char *)pwd);

    uint32_t t_cost = 2;            // 2-pass computation
    uint32_t m_cost = (1<<16);      // 64 mebibytes memory usage
    uint32_t parallelism = 1;       // number of threads and lanes

    // high-level API
    argon2i_hash_raw(t_cost, m_cost, parallelism, pwd, pwdlen, salt, SALTLEN, hash, HASHLEN);
    printf("%s", hash);
}
