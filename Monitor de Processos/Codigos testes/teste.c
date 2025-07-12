#include <windows.h>
#include <stdio.h>

#define NUM_PROCS 7

PROCESS_INFORMATION pi[NUM_PROCS];
STARTUPINFOA si[NUM_PROCS];

void encerrarUmProcesso() {
    DWORD pidEscolhido;
    int encontrado = 0;

    printf("\nDigite o PID do processo que deseja encerrar: ");
    scanf("%lu", &pidEscolhido);

    for (int i = 0; i < NUM_PROCS; i++) {
        if (pi[i].dwProcessId == pidEscolhido) {
            TerminateProcess(pi[i].hProcess, 0);
            CloseHandle(pi[i].hProcess);
            CloseHandle(pi[i].hThread);
            pi[i].dwProcessId = 0; // marca como encerrado
            printf("Processo com PID %lu encerrado.\n", pidEscolhido);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("PID %lu não encontrado entre os processos criados.\n", pidEscolhido);
    }
}

void criarProcessos() {
    for (int i = 0; i < NUM_PROCS; i++) {
        ZeroMemory(&si[i], sizeof(STARTUPINFOA));
        si[i].cb = sizeof(STARTUPINFOA);
        ZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));

        BOOL criado = CreateProcessA(
            NULL,
            "notepad.exe",
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si[i],
            &pi[i]
        );

        if (criado) {
            printf("Notepad criado com PID %lu\n", pi[i].dwProcessId);
        } else {
            pi[i].dwProcessId = 0;
            printf("Falha ao criar notepad no índice %d. Erro: %lu\n", i, GetLastError());
        }
    }
}

int main() {
    ZeroMemory(pi, sizeof(pi));
    criarProcessos();

    while (1) {
        printf("\n=== Gerenciador de Processos ===\n");
        printf("%-6s %-20s\n", "PID", "Nome do Processo");
        printf("---------------------------------\n");

        for (int i = 0; i < NUM_PROCS; i++) {
            if (pi[i].dwProcessId != 0) {
                printf("%-6lu %-20s\n", pi[i].dwProcessId, "notepad.exe");
            }
        }

        printf("\nMenu\n");
        printf("1 - Escolher um processo para encerrar\n");
        printf("2 - Encerrar o programa e todos os processos\n");
        printf("Opcao: ");

        int opcao;
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                encerrarUmProcesso();
                break;
            case 2:
                printf("Encerrando todos os processos...\n");
                for (int i = 0; i < NUM_PROCS; i++) {
                    if (pi[i].dwProcessId != 0) {
                        TerminateProcess(pi[i].hProcess, 0);
                        CloseHandle(pi[i].hProcess);
                        CloseHandle(pi[i].hThread);
                        pi[i].dwProcessId = 0;
                    }
                }
                printf("Todos os processos foram encerrados. Encerrando o programa.\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        system("pause");
        system("cls");
    }

    return 0;
}
