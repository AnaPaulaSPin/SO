import ctypes

# Definindo constantes
STD_INPUT_HANDLE = -10
STD_OUTPUT_HANDLE = -11

# Carregar as funções da API do Windows para leitura e escrita no console
kernel32 = ctypes.windll.kernel32

# Função para ler da entrada padrão (teclado)
def read_console():
    buffer = ctypes.create_string_buffer(256)  # Buffer para armazenar a entrada
    n = ctypes.c_ulong(0)  # Número de caracteres lidos
    kernel32.ReadConsoleA(kernel32.GetStdHandle(STD_INPUT_HANDLE), buffer, 256, ctypes.byref(n), None)
    return buffer.raw[:n.value]

# Função para escrever na saída padrão (tela)
def write_console(message):
    kernel32.WriteConsoleA(kernel32.GetStdHandle(STD_OUTPUT_HANDLE), message, len(message), None, None)


write_console(b"Digite uma string: ")  # Imprime a mensagem no console

# Lê a entrada do usuário (teclado)
buffer = read_console()  # Lê diretamente do stdin (console)

# Se tiver um '\n' no final,ele vai remover
if buffer.endswith(b'\n'):
    buffer = buffer[:-1]


# Inverte e imprime a string caractere por caractere
for i in reversed(buffer):
    write_console(bytes([i])) 

write_console(b"\n")
