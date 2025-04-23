#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
    char buffer[256];
    clock_t start, end;
    double time_taken;

    // Inicia a contagem do tempo
    start = clock();

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

    // Finaliza a contagem do tempo
    end = clock();
    
    // Calcula o tempo total de execução
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.5f segundos\n", time_taken);

    return 0;
}
