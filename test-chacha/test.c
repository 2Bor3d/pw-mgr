#include "cipher.h"
#include "chacha.h"
//#include <openssl/cipher.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Define your key (256-bit) and nonce (96-bit)
    uint8_t key[32] = { "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", 
        "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", 
        "a", "a", "a", "a", "a", "a", "a" };
    uint8_t nonce[12] = { "a", "a", "a", "a", "a", "a", "a", "a", "a", "a",
        "a", "a"  };
    uint32_t counter = 1;

    // Your data to encrypt/decrypt
    uint8_t plaintext[] = "Hello, ChaCha20!";
    size_t plaintext_len = sizeof(plaintext);
    uint8_t ciphertext[plaintext_len];
    uint8_t tag[16]; // Poly1305 tag

    // Initialize the ChaCha20 context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_chacha20_poly1305(), NULL, key, nonce);

    // Encrypt the data
    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);

    // Get the authentication tag
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_GET_TAG, 16, tag);

    // Print the result
    printf("Ciphertext: ");
    for (size_t i = 0; i < plaintext_len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\nTag: ");
    for (size_t i = 0; i < 16; i++) {
        printf("%02x ", tag[i]);
    }
    printf("\n");

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    return 0;
}
