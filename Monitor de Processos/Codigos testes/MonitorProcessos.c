#include <windows.h>
#include <stdio.h>

#define NUM_PROCS 7

int main() {
    PROCESS_INFORMATION pi[NUM_PROCS];
    STARTUPINFOA si[NUM_PROCS];
    int i;

    // Inicializa estruturas e cria processos silenciosamente
    for (i = 0; i < NUM_PROCS; i++) {
        ZeroMemory(&si[i], sizeof(STARTUPINFOA));
        si[i].cb = sizeof(STARTUPINFOA);
        ZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));

        CreateProcessA(
            NULL,
            "notepad.exe",
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si[i],
            &pi[i]);
    }

    // Agora imprime só a lista dos processos criados
    printf("\n=== Lista dos processos criados ===\n");
    printf("%-6s %-30s\n", "PID", "Nome do Processo");
    printf("------------------------------------------\n");

    for (i = 0; i < NUM_PROCS; i++) {
        if (pi[i].dwProcessId != 0) {
            printf("%-6lu %-30s\n", pi[i].dwProcessId, "notepad.exe");
        }
    }

    printf("\nPressione ENTER para encerrar esses processos...\n");
    getchar();

    // Termina todos os processos criados
    for (i = 0; i < NUM_PROCS; i++) {
        TerminateProcess(pi[i].hProcess, 0);
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    printf("Todos os processos foram encerrados.\n");
    return 0;
}
