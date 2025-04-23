#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>

#define STDIN_FD  0  // 0 é a entrada padrão (teclado)
#define STDOUT_FD 1  // 1 é a saída padrão (tela)

int main() {
    char buffer[256];  // Buffer para armazenar a string
    long len;          // Aqui vai o tamanho da string lida
    clock_t start, end;
    double time_taken;

    // Inicia a contagem do tempo
    start = clock();

    // Pedir pro usuário digitar a string
    const char *msg1 = "Digite uma string: ";
    syscall(SYS_write, STDOUT_FD, msg1, 19);  // Imprime no terminal usando syscall

    // Ler o que o usuário digitar
    len = syscall(SYS_read, STDIN_FD, buffer, sizeof(buffer));  // Lê direto do teclado

    // Se o usuário apertou Enter, remove o '\n' do final
    if (len > 0 && buffer[len - 1] == '\n') {
        len--;  // Desconta o '\n'
    }

    // Imprime a mensagem "String invertida:"
    const char *msg2 = "String invertida: ";
    syscall(SYS_write, STDOUT_FD, msg2, 18);  // Mais uma syscall pra imprimir

    // Agora vamos inverter a string
    for (long i = len - 1; i >= 0; i--) {
        syscall(SYS_write, STDOUT_FD, &buffer[i], 1);  // Imprime cada caractere
    }

    // Adiciona uma nova linha no final
    char newline = '\n';
    syscall(SYS_write, STDOUT_FD, &newline, 1);  // Imprime a nova linha

    // Finaliza a contagem do tempo
    end = clock();

    // Calcula o tempo total de execução
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    const char *msg3 = "Tempo de execução: ";
    syscall(SYS_write, STDOUT_FD, msg3, 19);  // Imprime a mensagem de tempo
    char time_str[50];
    sprintf(time_str, "%.5f segundos\n", time_taken);
    syscall(SYS_write, STDOUT_FD, time_str, strlen(time_str));  // Imprime o tempo de execução

    return 0;  // Termina o programa
}
