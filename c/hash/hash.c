#include "argon2.h"
#include <stdint.h>
#include <string.h>

void hash(uint8_t *result, char *password, char *salt)
{
    uint8_t hashlen = 32;
    uint8_t *pwd;
    memcpy(pwd, &password, sizeof(password));
    uint32_t pwdlen = strlen((char *)pwd);

    uint32_t t_cost = 2;            // 2-pass computation
    uint32_t m_cost = (1<<16);      // 64 mebibytes memory usage
    uint32_t parallelism = 1;       // number of threads and lanes

    // high-level API
    argon2i_hash_raw(t_cost, 
                     m_cost, 
                     parallelism, 
                     pwd, 
                     strlen(password), 
                     salt, 
                     sizeof(salt), 
                     result, 
                     hashlen);
}

