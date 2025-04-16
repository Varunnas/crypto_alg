#include <stdio.h>
#include <ctype.h>
#include <string.h>


void atbash_cipher(char *input, char *output) {
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (isalpha(c)) {
            if (isupper(c)) {
                output[i] = 'Z' - (c - 'A');
            } else {
                output[i] = 'z' - (c - 'a');
            }
        } else {
            output[i] = c;  
        }
    }
    output[strlen(input)] = '\0'; 
}

int main() {
    char text[256];
    char encrypted[256];

    printf("Enter text to encrypt using Atbash cipher: ");
    fgets(text, sizeof(text), stdin);

    
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    atbash_cipher(text, encrypted);

    printf("Encrypted text: %s\n", encrypted);

    return 0;
}