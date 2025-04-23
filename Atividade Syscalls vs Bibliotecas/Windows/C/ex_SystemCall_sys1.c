#include <windows.h>  // WinAPI

#define STDIN_FD  0  // 0 é a entrada padrão (teclado)
#define STDOUT_FD 1  // 1 é a saída padrão (tela)

int main() {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);  // Handle para a saída padrão (tela)
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);    // Handle para a entrada padrão (teclado)
    
    char buffer[256];  // Buffer para armazenar a string
    DWORD len;         // Aqui vai o tamanho da string lida

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

    return 0;  // Termina o programa
}
