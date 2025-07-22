// i joinked the argon2 implementation from:
// https://github.com/P-H-C/phc-winner-argon2/
//
// i joinked the chacha20 implementation from:
// https://github.com/marcizhu/ChaCha20
//
// i joinked the json implementation from:
// https://github.com/kgabis/parson

#include "store/store.h"
#include "hash/hash.h"
#include "crypt/crypt.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_new(struct store *new, char *info, char *nonce, char *salt, char *data) {
    new->info = info;
    new->same = 0;
    memcpy(new->nonce, nonce, 96);
    new->salt = salt;
    new->data = data;
}

int main() 
{
    printf("inizialised\n");
    struct store data;
    load_file(&data, "store/test.json");
    uint8_t result[32];
    hash(result, "hello world", data.salt);
    for( int i=0; i<32; ++i ) printf( "%02x", (result)[i] ); printf( "\n" );
    size_t string_len = strlen(data.data);
    printf("len: %zu\n", string_len);
    uint8_t* string = (uint8_t*)malloc((string_len)*sizeof(uint8_t));
    memcpy(string, data.data, string_len+1);
    printf("%s\n", string);

    printf("nonce: %s\n", data.nonce);
    encrypt(result, data.nonce, string);
    printf("-----------------------------");
    printf("string: %s\n", string);
    encrypt(result, data.nonce, string);
    printf("%s\n", string);
    printf("%s\n", data.data);
}
