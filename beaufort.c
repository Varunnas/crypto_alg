#include <stdio.h>
#include <string.h>
#include <ctype.h>

void repeat_key(const char *text, const char *key, char *full_key) {
    int key_len = strlen(key), j = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            full_key[i] = key[j++ % key_len];
        } else {
            full_key[i] = text[i];
        }
    }
    full_key[strlen(text)] = '\0';
}

void beaufort_cipher(const char *text, const char *key, char *output) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int t = text[i] - base;
            int k = (isupper(key[i]) ? key[i] - 'A' : key[i] - 'a');
            output[i] = base + (k - t + 26) % 26;
        } else {
            output[i] = text[i];
        }
    }
    output[strlen(text)] = '\0';
}

int main() {
    char text[256], keyword[256], full_key[256];
    char encrypted[256], decrypted[256];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    repeat_key(text, keyword, full_key);

    beaufort_cipher(text, full_key, encrypted);
    printf("Encrypted: %s\n", encrypted);

    beaufort_cipher(encrypted, full_key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
