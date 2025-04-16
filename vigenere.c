#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_key(const char *text, const char *keyword, char *key) {
    int j = 0;
    for (int i = 0; text[i]; i++) {
        key[i] = isalpha(text[i]) ? keyword[j++ % strlen(keyword)] : text[i];
    }
    key[strlen(text)] = '\0';
}

void vigenere_cipher(const char *text, const char *key, char *output, int encrypt) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char shift = (key[i] - (isupper(key[i]) ? 'A' : 'a'));
            if (!encrypt) shift = 26 - shift;
            output[i] = ((text[i] - base + shift) % 26) + base;
        } else {
            output[i] = text[i];
        }
    }
    output[strlen(text)] = '\0';
}

int main() {
    char text[256], keyword[256], key[256], encrypted[256], decrypted[256];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    generate_key(text, keyword, key);

    vigenere_cipher(text, key, encrypted, 1);
    printf("Encrypted text: %s\n", encrypted);

    vigenere_cipher(encrypted, key, decrypted, 0);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
