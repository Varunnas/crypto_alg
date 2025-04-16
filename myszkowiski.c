#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void to_upper(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int compare(const void *a, const void *b) {
    return ((char *)a)[0] - ((char *)b)[0];
}

void get_order(char *key, int order[]) {
    int len = strlen(key);
    char temp[len + 1];
    strcpy(temp, key);

    char sorted[len + 1];
    strcpy(sorted, key);
    qsort(sorted, len, sizeof(char), compare);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (temp[i] == sorted[j]) {
                order[i] = j;
                sorted[j] = ' '; 
                break;
            }
        }
    }
}


void myszkowski_encrypt(char *text, char *key, char *encrypted) {
    to_upper(text);
    to_upper(key);

    int key_len = strlen(key);
    int text_len = strlen(text);

    int rows = (text_len + key_len - 1) / key_len;
    int padded_len = rows * key_len;
    char padded[padded_len + 1];
    strcpy(padded, text);
    for (int i = text_len; i < padded_len; i++)
        padded[i] = 'X'; 
    padded[padded_len] = '\0';

    char matrix[rows][key_len];
    int index = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < key_len; j++)
            matrix[i][j] = padded[index++];

    int order[key_len];
    get_order(key, order);

    index = 0;
    for (int k = 0; k < key_len; k++) {
        for (int i = 0; i < key_len; i++) {
            if (order[i] == k) {
                for (int r = 0; r < rows; r++)
                    encrypted[index++] = matrix[r][i];
                break;
            }
        }
    }
    encrypted[index] = '\0';
}

int main() {
    char text[256], key[64], encrypted[256];

    printf("Enter plaintext (no spaces): ");
    scanf("%s", text);
    printf("Enter keyword: ");
    scanf("%s", key);

    myszkowski_encrypt(text, key, encrypted);
    printf("Encrypted (Myszkowski Cipher): %s\n", encrypted);

    return 0;
}