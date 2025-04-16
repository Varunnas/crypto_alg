#include <stdio.h>
#include <string.h>
#include <ctype.h>

void running_key_cipher(const char *input, const char *key, char *output, int encrypt) {
    for (int i = 0, j = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            char base = isupper(input[i]) ? 'A' : 'a';
            char k_base = isupper(key[j]) ? 'A' : 'a';
            int shift = key[j] - k_base;

            output[i] = ((input[i] - base + (encrypt ? shift : (26 - shift))) % 26) + base;
            j++;
        } else {
            output[i] = input[i];
        }
    }
    output[strlen(input)] = '\0';
}

int main() {
    char text[512], key[512], encrypted[512], decrypted[512];

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter running key (at least as long as the text): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    if (strlen(key) < strlen(text)) {
        printf("Error: Key is too short.\n");
        return 1;
    }

    running_key_cipher(text, key, encrypted, 1);
    printf("Encrypted: %s\n", encrypted);

    running_key_cipher(encrypted, key, decrypted, 0);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
