#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEXT_SIZE 256

void generate_ngrams(const char *text, int n, char ngrams[][n + 1], int *ngram_count) {
    int len = strlen(text);
    *ngram_count = 0;
    for (int i = 0; i <= len - n; i++) {
        strncpy(ngrams[*ngram_count], text + i, n);
        ngrams[*ngram_count][n] = '\0'; 
        (*ngram_count)++;
    }
}

void encrypt_ngram(const char *text, int n, const char *substitute[], char *encrypted) {
    char ngrams[MAX_TEXT_SIZE][n + 1];
    int ngram_count = 0;

    generate_ngrams(text, n, ngrams, &ngram_count);

    int encrypted_index = 0;
    for (int i = 0; i < ngram_count; i++) {
        int found = 0;
        for (int j = 0; substitute[j] != NULL; j++) {
            if (strcmp(ngrams[i], substitute[j]) == 0) {
                strcpy(encrypted + encrypted_index, substitute[j]);
                encrypted_index += n;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(encrypted + encrypted_index, ngrams[i]);
            encrypted_index += n;
        }
    }
    encrypted[encrypted_index] = '\0'; 
}

void decrypt_ngram(const char *ciphertext, int n, const char *substitute[], char *decrypted) {
    char ngrams[MAX_TEXT_SIZE][n + 1];
    int ngram_count = 0;

    generate_ngrams(ciphertext, n, ngrams, &ngram_count);

    char *reverse_substitute[MAX_TEXT_SIZE];
    for (int i = 0; substitute[i] != NULL; i++) {
        reverse_substitute[i] = (char *)malloc(n + 1);
        for (int j = 0; substitute[j] != NULL; j++) {
            if (strcmp(substitute[i], substitute[j]) == 0) {
                reverse_substitute[j] = substitute[i];
            }
        }
    }

    int decrypted_index = 0;
    for (int i = 0; i < ngram_count; i++) {
        int found = 0;
        for (int j = 0; substitute[j] != NULL; j++) {
            if (strcmp(ngrams[i], substitute[j]) == 0) {
                strcpy(decrypted + decrypted_index, reverse_substitute[j]);
                decrypted_index += n;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(decrypted + decrypted_index, ngrams[i]);
            decrypted_index += n;
        }
    }

    decrypted[decrypted_index] = '\0';  
}

int main() {
    char text[MAX_TEXT_SIZE], encrypted[MAX_TEXT_SIZE], decrypted[MAX_TEXT_SIZE];
    int n;

    const char *substitute[] = {"AB", "CD", "EF", "GH", NULL}; 

    printf("Enter plaintext (A-Z only, no spaces): ");
    scanf("%s", text);

    printf("Enter n-gram size (n): ");
    scanf("%d", &n);

    encrypt_ngram(text, n, substitute, encrypted);
    printf("Encrypted: %s\n", encrypted);

    decrypt_ngram(encrypted, n, substitute, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
