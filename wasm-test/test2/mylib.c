#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to process a string
char* process_string(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    
    size_t len = strlen(input);
    char* result = (char*)malloc(len + 50); // Allocate extra space
    
    if (result == NULL) {
        return NULL;
    }
    
    strcpy(result, "Processed: ");
    strcat(result, input);
    strcat(result, " (WASM)");
    
    return result;
}

// Function to free memory allocated by process_string
void free_string(char* str) {
    if (str != NULL) {
        free(str);
    }
}

// Another example function
char* reverse_string(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    
    size_t len = strlen(input);
    char* result = (char*)malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        result[i] = input[len - 1 - i];
    }
    result[len] = '\0';
    
    return result;
}

// And now me:
void add_char(char *string, char character) {
    while (*string++);
    *(string - 1) = character;
    *string = '\0';
}


char* generate() {
    //srand(time(NULL));

    const char characters[] = "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "1234567890";
        //"^!\"$%&/()=?*'_:;,.-#+~@{[]}\\";

    const int length = 20;

    char* password = (char*)malloc(length+50);
    *password = '\0';
    //printf("empty: %s\n", password);
    int random;
    char character;

    for (int i=0; i<length; i++) {
        random = rand() % strlen(characters);
        character = characters[random];

        //printf("%c ", characters[random]);
        //printf("i: %i ; r: %i\n", i, random);

        add_char(password, characters[random]);
        //printf("pwd: %s\n", password);
        //strcat(password, &character);
    }

    return password;
}
#include <stdio.h>
int main() {
    printf("DONE: %s\n-----------\n", generate());
    char *result = NULL;
    result = generate();
    //while (*result++) {
    //    printf("%c\n", *result);
    //}
    free_string(result);
}

