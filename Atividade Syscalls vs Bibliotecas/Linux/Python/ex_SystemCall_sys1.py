import os #Biblioteca System Call Linux

# Mensagem antes de pedir a string
os.write(1, b"Digite uma string: ")  # Imprime no terminal usando SYS_write (stdout)

# Lê a entrada do usuário (teclado)
buffer = os.read(0, 256)  # Lê diretamente do stdin (fd 0)

# Se tiver um '\n' no final, remove
if buffer.endswith(b'\n'):
    buffer = buffer[:-1]  # Remove o '\n'

# Mensagem antes de mostrar a string invertida
os.write(1, b"String invertida: ")  # Imprime a mensagem "String invertida:"

# Inverte e imprime a string caractere por caractere
for i in reversed(buffer):
    os.write(1, bytes([i]))  # Imprime cada caractere de trás pra frente

# Adiciona uma nova linha no final
os.write(1, b"\n")  # Imprime a nova linha
