#include <stdio.h>
#include <string.h>
#include <ctype.h>

void repeat_key(const char *text, const char *key_digits, int *key_array) {
    int key_len = strlen(key_digits), j = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            key_array[i] = key_digits[j++ % key_len] - '0';
        } else {
            key_array[i] = -1;
        }
    }
}

void gronsfeld_encrypt(const char *text, const int *key_array, char *encrypted) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i]) && key_array[i] >= 0) {
            char base = isupper(text[i]) ? 'A' : 'a';
            encrypted[i] = ((text[i] - base + key_array[i]) % 26) + base;
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[strlen(text)] = '\0';
}

void gronsfeld_decrypt(const char *encrypted, const int *key_array, char *decrypted) {
    for (int i = 0; encrypted[i]; i++) {
        if (isalpha(encrypted[i]) && key_array[i] >= 0) {
            char base = isupper(encrypted[i]) ? 'A' : 'a';
            decrypted[i] = ((encrypted[i] - base - key_array[i] + 26) % 26) + base;
        } else {
            decrypted[i] = encrypted[i];
        }
    }
    decrypted[strlen(encrypted)] = '\0';
}

int main() {
    char text[256], key_digits[256], encrypted[256], decrypted[256];
    int key_array[256];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter numeric key (e.g., 31415): ");
    fgets(key_digits, sizeof(key_digits), stdin);
    key_digits[strcspn(key_digits, "\n")] = '\0';

    repeat_key(text, key_digits, key_array);

    gronsfeld_encrypt(text, key_array, encrypted);
    printf("Encrypted text: %s\n", encrypted);

    gronsfeld_decrypt(encrypted, key_array, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
