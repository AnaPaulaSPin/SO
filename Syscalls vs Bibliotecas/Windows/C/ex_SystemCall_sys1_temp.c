#include <windows.h>  // WinAPI
#include <stdio.h>    // Para usar strlen

#define STDIN_FD  0  // 0 é a entrada padrão (teclado)
#define STDOUT_FD 1  // 1 é a saída padrão (tela)

int main() {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);  // Handle para a saída padrão (tela)
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);    // Handle para a entrada padrão (teclado)

    char buffer[256];  // Buffer para armazenar a string
    DWORD len;         // Aqui vai o tamanho da string lida

    // Inicia a contagem de tempo
    DWORD start_time = GetTickCount();  // Usando GetTickCount para capturar o tempo

    // Pedir pro usuário digitar a string
    const char *msg1 = "Digite uma string: ";
    WriteConsoleA(hStdout, msg1, strlen(msg1), &len, NULL);  // Imprime no terminal usando WriteConsoleA

    // Ler o que o usuário digitar
    ReadConsoleA(hStdin, buffer, sizeof(buffer), &len, NULL);  // Lê direto do teclado

    // Se o usuário apertou Enter, remove o '\n' do final
    if (len > 0 && buffer[len - 1] == '\n') {
        len--;  // Descarta o '\n'
    }

    // Agora vamos inverter a string
    for (long i = len - 1; i >= 0; i--) {
        WriteConsoleA(hStdout, &buffer[i], 1, &len, NULL);  // Imprime cada caractere invertido
    }

    // Adiciona uma nova linha no final
    const char newline = '\n';
    WriteConsoleA(hStdout, &newline, 1, &len, NULL);  // Imprime a nova linha

    // Finaliza a contagem de tempo
    DWORD end_time = GetTickCount();  // Usando GetTickCount para capturar o tempo de finalização

    // Calcula o tempo total de execução
    DWORD execution_time = end_time - start_time;

    // Imprime o tempo de execução
    char time_msg[50];
    sprintf(time_msg, "Tempo de execução: %lu ms\n", execution_time);
    WriteConsoleA(hStdout, time_msg, strlen(time_msg), &len, NULL);  // Imprime o tempo de execução

    return 0;  // Termina o programa
}
