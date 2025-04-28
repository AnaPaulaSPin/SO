#include <stdio.h>
#include <string.h>

int main() {
    char buffer[256];

    printf("Digite uma string: ");              
    fgets(buffer, sizeof(buffer), stdin);       

    // Remove o '\n' do final, se presente
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    printf("String invertida: ");               /
    for (int i = len - 1; i >= 0; i--) {
        putchar(buffer[i]);                     
    }

    putchar('\n');                            
    return 0;
}
