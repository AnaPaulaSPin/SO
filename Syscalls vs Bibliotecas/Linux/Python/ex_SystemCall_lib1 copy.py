import time

# Inicia a contagem do tempo
start_time = time.time()

# Leitura da string
s = input("Digite uma string: ")

# Impressão da string invertida
print("String invertida:", s[::-1])

# Finaliza a contagem do tempo
end_time = time.time()

# Calcula o tempo total de execução
execution_time = end_time - start_time

# Imprime o tempo de execução
print(f"Tempo de execução: {execution_time:.5f} segundos")
