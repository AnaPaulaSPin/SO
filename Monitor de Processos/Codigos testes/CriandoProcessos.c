#include <windows.h>
#include <stdio.h>

#define NUM_PROCS 7

int main() {
    PROCESS_INFORMATION pi[NUM_PROCS];
    STARTUPINFOA si[NUM_PROCS];
    int i;

    // Inicializa estruturas e cria processos
    for (i = 0; i < NUM_PROCS; i++) {
        ZeroMemory(&si[i], sizeof(STARTUPINFOA));
        si[i].cb = sizeof(STARTUPINFOA);
        ZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));

        if (!CreateProcessA(
                NULL,
                "notepad.exe",   // Programa a executar
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si[i],
                &pi[i])) {
            printf("Falha ao criar processo %d. Erro: %lu\n", i + 1, GetLastError());
        } else {
            printf("Processo %d criado com PID: %lu\n", i + 1, pi[i].dwProcessId);
        }
    }

    // Espera do usuário para manter os processos abertos
    printf("Pressione ENTER para encerrar todos os processos...\n");
    getchar();

    // Fecha os handles e termina os processos
    for (i = 0; i < NUM_PROCS; i++) {
        TerminateProcess(pi[i].hProcess, 0);
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    printf("Todos os processos foram encerrados.\n");
    return 0;
}
