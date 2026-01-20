#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void add_char(char *string, char character) {
    while (*string++);
    *(string - 1) = character;
    *string = '\0';
}


char* generate() {
    srand(time(NULL));

    const char characters[] = "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "1234567890"
        "^!\"$%&/()=?*'_:;,.-#+~@{[]}\\";

   const int length = 128;

    char *password = malloc(length);
    *password = '\0';
    printf("empty: %s\n", password);
    int random;

    for (int i=0; i<length; i++) {
        random = rand() % strlen(characters);

        printf("%c ", characters[random]);
        printf("i: %i ; r: %i\n", i, random);

        add_char(password, characters[random]);
        printf("pwd: %s\n", password);
    }

    return password;
}

int main() {
    char *result = generate();
    printf("DONE: %s\n", result);
    return 0;
}

