#include <windows.h> // Inclui a API do Windows para criar processos, manipular handles, etc.
#include <psapi.h>   // Biblioteca para pegar informações sobre o uso de memória dos processos
#include <stdio.h>   // Entrada e saída padrão (printf, scanf)

// Defino o número máximo de processos que vou criar
#define NUM_PROCS 7

// Declaro vetores globais para armazenar informações dos processos criados
PROCESS_INFORMATION pi[NUM_PROCS]; // Contém o handle e o PID do processo
STARTUPINFOA si[NUM_PROCS];         // Estrutura para inicialização dos processos

// Função para encerrar um processo específico dado o seu PID
void encerrarUmProcesso(){
    DWORD pidEscolhido;
    int encontrado = 0;

    // Peço ao usuário o PID do processo que ele quer encerrar
    printf("\nDigite o PID do processo que deseja encerrar: ");
    scanf("%lu", &pidEscolhido);

    // Percorro todos os processos que eu mesma criei
    for (int i = 0; i < NUM_PROCS; i++) {
        // Se o PID bater com algum dos meus processos
        if (pi[i].dwProcessId == pidEscolhido) {
            // Tenta encerrar o processo e fechar os handles
            TerminateProcess(pi[i].hProcess, 0);
            CloseHandle(pi[i].hProcess);
            CloseHandle(pi[i].hThread);

            // Marco o PID como 0 para indicar que foi encerrado
            pi[i].dwProcessId = 0;

            printf("Processo com PID %lu encerrado.\n", pidEscolhido);
            encontrado = 1;
            break;
        }
    }

    // Se não achou o PID nos processos criados
    if (!encontrado) {
        printf("PID %lu não encontrado entre os processos criados.\n", pidEscolhido);
    }
}

// Função que cria os processos (no caso, 7 Notepads)
void criarProcessos(){
    for (int i = 0; i < NUM_PROCS; i++) {
        // Zera as estruturas para evitar lixo de memória
        ZeroMemory(&si[i], sizeof(STARTUPINFOA));
        si[i].cb = sizeof(STARTUPINFOA); // precisa informar o tamanho
        ZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));

        // Cria o processo, nesse caso o Notepad
        if (CreateProcessA(
                NULL,            // Nome do módulo (NULL usa o command line)
                "notepad.exe",   // O comando a ser executado
                NULL, NULL,      // Segurança do processo e thread
                FALSE,           // Não herda handles
                0,               // Flags
                NULL, NULL,      // Ambiente e diretório atual
                &si[i], &pi[i])) // Estruturas de input/output e info do processo
        {
        } 
    }
}

// Função para imprimir a memória usada por um processo em KB
void printMemoriaDoProcesso(HANDLE hProcess) {
    PROCESS_MEMORY_COUNTERS pmc;

    // Usa GetProcessMemoryInfo para pegar a memória usada
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        printf("%lu KB", pmc.WorkingSetSize / 1024);
    } else {
        printf("N/A");
    }
}

// Função principal
int main() {
    // Primeiro cria os processos
    criarProcessos();

    while (1) {
        // Exibe o cabeçalho do monitor
        printf("\n=== Monitor de Processos ===\n");
        printf("%-6s %-20s %-15s\n", "PID", "Nome do Processo", "Mem. (KB)");
        printf("-------------------------------------------------\n");

        // Lista todos os processos que ainda estão ativos
        for (int i = 0; i < NUM_PROCS; i++) {
            if (pi[i].dwProcessId != 0) { // só mostra os que ainda existem(caso o usuario tenha encerrado algum processo)
                printf("%-6lu %-20s ", pi[i].dwProcessId, "notepad.exe");
                printMemoriaDoProcesso(pi[i].hProcess);
                printf("\n");
            }
        }

        // Menu de opções
        printf("\nMenu:\n");
        printf("1 - Encerrar um processo\n");
        printf("2 - Encerrar todos e sair\n");
        printf("Opcao: ");
        
        int opcao;
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Caso queira encerrar apenas um processo
            encerrarUmProcesso();
        } else if (opcao == 2) {
            // Caso queira encerrar tudo
            printf("Encerrando todos os processos criados...\n");
            for (int i = 0; i < NUM_PROCS; i++) {
                if (pi[i].dwProcessId != 0) {
                    TerminateProcess(pi[i].hProcess, 0);
                    CloseHandle(pi[i].hProcess);
                    CloseHandle(pi[i].hThread);
                }
            }
            printf("Todos encerrados. Saindo...\n");
            break;
        } else {
            printf("Opcao inválida.\n");
        }

        // Pausa para o usuário ver e depois limpa a tela para ficar organizado e melhor para ve
        system("pause");
        system("cls");
    }

    return 0;
}
