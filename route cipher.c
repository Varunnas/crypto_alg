#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void pad_plaintext(char *text, int rows, int cols) {
    int len = strlen(text);
    int total = rows * cols;
    for (int i = len; i < total; i++) {
        text[i] = 'X';  
    }
    text[total] = '\0';  
}

void sanitize_input(char *text) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (!isalpha(text[i])) {
            for (int j = i; j < len; j++) {
                text[j] = text[j + 1];
            }
            len--;
            i--;  
        } else {
            text[i] = toupper(text[i]);  
        }
    }
}

void route_encrypt(char *text, int rows, int cols, char *encrypted) {
    char matrix[rows][cols];
    int k = 0;

    pad_plaintext(text, rows, cols);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = text[k++];

    k = 0;
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            encrypted[k++] = matrix[i][j];

    encrypted[k] = '\0';  

void route_decrypt(char *cipher, int rows, int cols, char *decrypted) {
    char matrix[rows][cols];
    int k = 0;

    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            matrix[i][j] = cipher[k++];

    k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            decrypted[k++] = matrix[i][j];

    decrypted[k] = '\0';  

int main() {
    char text[256], encrypted[256], decrypted[256];
    int rows, cols;

    printf("Enter plaintext (A-Z only, no spaces): ");
    scanf("%s", text);
    sanitize_input(text);  

    printf("Enter matrix dimensions (rows cols): ");
    scanf("%d %d", &rows, &cols);

    if (rows * cols < strlen(text)) {
        printf("Error: Matrix size is too small for the plaintext.\n");
        return 1;
    }

    // Encrypt the text
    route_encrypt(text, rows, cols, encrypted);
    printf("Encrypted: %s\n", encrypted);

    // Decrypt the cipher text
    route_decrypt(encrypted, rows, cols, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
