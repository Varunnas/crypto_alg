#include <stdio.h>
#include <ctype.h>
#include <string.h>

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}

void affine_encrypt(char *in, char *out, int a, int b) {
    for (int i = 0; in[i]; i++) {
        if (isalpha(in[i])) {
            char base = isupper(in[i]) ? 'A' : 'a';
            out[i] = ((a * (in[i] - base) + b) % 26) + base;
        } else {
            out[i] = in[i];
        }
    }
    out[strlen(in)] = '\0';
}

void affine_decrypt(char *in, char *out, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("Invalid key: 'a' must be coprime with 26.\n");
        return;
    }

    for (int i = 0; in[i]; i++) {
        if (isalpha(in[i])) {
            char base = isupper(in[i]) ? 'A' : 'a';
            out[i] = (a_inv * (in[i] - base - b + 26) % 26) + base;
        } else {
            out[i] = in[i];
        }
    }
    out[strlen(in)] = '\0';
}

int main() {
    char text[256], encrypted[256], decrypted[256];
    int a, b;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter key 'a' (coprime with 26): ");
    scanf("%d", &a);
    printf("Enter key 'b': ");
    scanf("%d", &b);

    if (mod_inverse(a, 26) == -1) {
        printf("Invalid 'a'. Must be coprime with 26.\n");
        return 1;
    }

    affine_encrypt(text, encrypted, a, b);
    printf("Encrypted: %s\n", encrypted);

    affine_decrypt(encrypted, decrypted, a, b);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
