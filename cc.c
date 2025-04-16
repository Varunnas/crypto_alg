#include <stdio.h>
#include <ctype.h>
#include <string.h>

void caesar_encrypt(char *input, char *output, int key) {
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            output[i] = ((c - base + key) % 26) + base;
        } else {
            output[i] = c; 
        }
    }
    output[strlen(input)] = '\0';
}

void caesar_decrypt(char *input, char *output, int key) {
    caesar_encrypt(input, output, 26 - (key % 26));
}

int main() {
    char text[256];
    char encrypted[256];
    char decrypted[256];
    int key;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }

    printf("Enter key (number of positions to shift): ");
    scanf("%d", &key);

    caesar_encrypt(text, encrypted, key);
    printf("Encrypted: %s\n", encrypted);

    caesar_decrypt(encrypted, decrypted, key);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
