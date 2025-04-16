#include <stdio.h>
#include <string.h>

#define MOD 26

int char_to_int(char c) {
    return c - 'A';
}

char int_to_char(int i) {
    return i + 'A';
}

int determinant(int key[2][2]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
}

int mod_inverse(int a) {
    a = a % MOD;
    for (int i = 1; i < MOD; i++) {
        if ((a * i) % MOD == 1)
            return i;
    }
    return -1; 
}

int inverse_key(int key[2][2], int inv[2][2]) {
    int det = determinant(key);
    int inv_det = mod_inverse(det);

    if (inv_det == -1) return 0; 
    inv[0][0] = (key[1][1] * inv_det) % MOD;
    inv[0][1] = (-key[0][1] * inv_det) % MOD;
    inv[1][0] = (-key[1][0] * inv_det) % MOD;
    inv[1][1] = (key[0][0] * inv_det) % MOD;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            inv[i][j] = (inv[i][j] + MOD) % MOD;

    return 1;
}

void encrypt_block(char *plaintext, int key[2][2], char *ciphertext) {
    int p[2];
    p[0] = char_to_int(plaintext[0]);
    p[1] = char_to_int(plaintext[1]);

    int c[2];
    c[0] = (key[0][0] * p[0] + key[0][1] * p[1]) % MOD;
    c[1] = (key[1][0] * p[0] + key[1][1] * p[1]) % MOD;

    ciphertext[0] = int_to_char(c[0]);
    ciphertext[1] = int_to_char(c[1]);
    ciphertext[2] = '\0'; 
}

void decrypt_block(char *ciphertext, int key[2][2], char *plaintext) {
    int inv_key[2][2];
    if (!inverse_key(key, inv_key)) {
        printf("Key matrix is not invertible!\n");
        return;
    }

    int c[2];
    c[0] = char_to_int(ciphertext[0]);
    c[1] = char_to_int(ciphertext[1]);

    int p[2];
    p[0] = (inv_key[0][0] * c[0] + inv_key[0][1] * c[1]) % MOD;
    p[1] = (inv_key[1][0] * c[0] + inv_key[1][1] * c[1]) % MOD;

    plaintext[0] = int_to_char((p[0] + MOD) % MOD); 
    plaintext[1] = int_to_char((p[1] + MOD) % MOD);
    plaintext[2] = '\0'; 
}

int main() {
    char text[3], ciphertext[3], decrypted[3];
    int key[2][2];

    printf("Enter 2x2 key matrix (row-wise):\n");
    scanf("%d %d %d %d", &key[0][0], &key[0][1], &key[1][0], &key[1][1]);

    printf("Enter 2-letter plaintext (uppercase only): ");
    scanf("%s", text);

    if (strlen(text) != 2) {
        printf("Error: Plaintext must be exactly 2 letters.\n");
        return 1;
    }

    encrypt_block(text, key, ciphertext);
    printf("Encrypted: %s\n", ciphertext);

    decrypt_block(ciphertext, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
