#include "crypt.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main()
{
    uint8_t key[32] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    uint8_t nonce[12] = "aaaaaaaaaaaa";
    uint8_t string[] = "sksksk";
    uint8_t data[sizeof(string)+2];
    memcpy(data, string, sizeof(string));

    encrypt(key, nonce, data);
    printf("%s\n", data);
    encrypt(key, nonce, data);

    printf("%s\n", data);
}
