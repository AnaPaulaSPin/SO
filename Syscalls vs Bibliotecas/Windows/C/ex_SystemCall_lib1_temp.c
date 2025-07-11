#include <stdio.h>
#include <string.h>

int main() {
    char buffer[256];

    printf("Digite uma string: ");              // <-- Impressão com printf (alto nível)
    fgets(buffer, sizeof(buffer), stdin);       // <-- Leitura com fgets (alto nível)

    // Remove o '\n' do final, se presente
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    printf("String invertida: ");               // <-- Impressão com printf
    for (int i = len - 1; i >= 0; i--) {
        putchar(buffer[i]);                     // <-- Escrita caractere por caractere (alto nível)
    }

    putchar('\n');                              // <-- Nova linha
    return 0;
}
