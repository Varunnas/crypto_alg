#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void encryptRailFence(const char *text, int rails, char *encrypted) {
    int len = strlen(text);
    char rail[rails][len];
    memset(rail, 0, sizeof(rail)); 

    int row = 0;
    bool down = true;

    for (int i = 0; i < len; i++) {
        rail[row][i] = text[i];

        if (row == 0)
            down = true;
        else if (row == rails - 1)
            down = false;

        row += down ? 1 : -1;
    }

    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != 0) {  
                encrypted[index++] = rail[i][j];
            }
        }
    }
    encrypted[index] = '\0';
}

void decryptRailFence(const char *cipher, int rails, char *decrypted) {
    int len = strlen(cipher);
    char rail[rails][len];
    memset(rail, 0, sizeof(rail));  

    int row = 0;
    bool down = true;

    for (int i = 0; i < len; i++) {
        rail[row][i] = '*';

        if (row == 0)
            down = true;
        else if (row == rails - 1)
            down = false;

        row += down ? 1 : -1;
    }

    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '*' && index < len) {
                rail[i][j] = cipher[index++];
            }
        }
    }

    row = 0;
    down = true;
    for (int i = 0; i < len; i++) {
        decrypted[i] = rail[row][i];

        if (row == 0)
            down = true;
        else if (row == rails - 1)
            down = false;

        row += down ? 1 : -1;
    }
    decrypted[len] = '\0';
}

int main() {
    char text[256], encrypted[256], decrypted[256];
    int rails;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter number of rails: ");
    scanf("%d", &rails);

    if (rails < 2) {
        printf("Error: Number of rails must be at least 2.\n");
        return 1;
    }

    encryptRailFence(text, rails, encrypted);
    printf("Encrypted: %s\n", encrypted);

    decryptRailFence(encrypted, rails, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
