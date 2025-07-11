#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <tchar.h>

int main() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    int count = 0;

    // Tira um snapshot dos processos do sistema
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        _tprintf(_T("Erro ao criar snapshot.\n"));
        return 1;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        _tprintf(_T("Erro ao obter primeiro processo.\n"));
        CloseHandle(hProcessSnap);
        return 1;
    }

    _tprintf(_T("%-6s %-30s\n"), _T("PID"), _T("Nome do Processo"));
    _tprintf(_T("----------------------------------------\n"));

    do {
        _tprintf(_T("%-6u %-30s\n"), pe32.th32ProcessID, pe32.szExeFile);
        count++;
        if (count >= 7) break;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return 0;
}
