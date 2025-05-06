#include "hash.h"
#include <stdint.h>
#include <stdio.h>

int main() {
    uint8_t result[32];
    hash(result, "hello world", "aaaa");
    for( int i=0; i<32; ++i ) printf( "%02x", (result)[i] ); printf( "\n" );
}
