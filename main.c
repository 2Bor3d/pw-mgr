// i joinked the argon2 implementation from:
// https://github.com/P-H-C/phc-winner-argon2/
//
// i joinked the chacha20 implementation from:
// https://github.com/openssh/openssh-portable

#include "argon2.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHLEN 32
#define SALTLEN 16

void hash(char* password, uint8_t* result) {
    uint8_t hash[HASHLEN];

    uint8_t salt[SALTLEN];
    memset(salt, 0x00, SALTLEN);

    uint8_t* pwd = (uint8_t *)strdup(password);
    uint32_t pwdlen = strlen((char *)pwd);

    uint32_t t_cost = 2;        // interations
    uint32_t m_cost = (1<<16);  // memory usage (64mb)
    uint32_t parallelism = 1;   // threads

    argon2id_hash_raw(
            t_cost, 
            m_cost, 
            parallelism, 
            pwd, 
            pwdlen, 
            salt, 
            SALTLEN,
            hash,
            HASHLEN
        );
    free(pwd);

    for (int i=0; i<HASHLEN; ++i) printf("%02x", hash[i]); printf("\n");
    result = hash;
}

int main() {
    char* password = "password";
    uint8_t* result;

    hash(password, result);
}
