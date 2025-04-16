#include <stdio.h>
#include <ctype.h>
#include <string.h>

void autokey_encrypt(char *plaintext, char *key, char *ciphertext) {
    int pt_len = strlen(plaintext);
    char full_key[256];

    strcpy(full_key, key);
    strncat(full_key, plaintext, pt_len - strlen(key));

    for (int i = 0; i < pt_len; i++) {
        char p = plaintext[i];
        char k = full_key[i];

        if (isalpha(p)) {
            char base = isupper(p) ? 'A' : 'a';
            char key_base = isupper(k) ? 'A' : 'a';
            ciphertext[i] = ((p - base + (tolower(k) - 'a')) % 26) + base;
        } else {
            ciphertext[i] = p;
        }
    }
    ciphertext[pt_len] = '\0';
}

void autokey_decrypt(char *ciphertext, char *key, char *plaintext) {
    int ct_len = strlen(ciphertext);
    char full_key[256];
    strcpy(full_key, key);

    for (int i = 0; i < ct_len; i++) {
        char c = ciphertext[i];
        char k = full_key[i];

        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char key_char = tolower(k) - 'a';
            char p = ((c - base - key_char + 26) % 26) + base;
            plaintext[i] = p;

            // Append decrypted char to key for next round
            int len = strlen(full_key);
            full_key[len] = tolower(p);
            full_key[len + 1] = '\0';
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[ct_len] = '\0';
}

int main() {
    char plaintext[256];
    char key[256];
    char ciphertext[256];
    char decrypted[256];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    size_t len = strlen(plaintext);
    if (len > 0 && plaintext[len - 1] == '\n') plaintext[len - 1] = '\0';

    printf("Enter key (word): ");
    scanf("%s", key);

    autokey_encrypt(plaintext, key, ciphertext);
    printf("Encrypted: %s\n", ciphertext);

    autokey_decrypt(ciphertext, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
