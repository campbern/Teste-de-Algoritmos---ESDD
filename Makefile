
# Compilador utilizado no projeto.
CC = gcc

# Opções de compilação.
# -Wall    : habilita diversos avisos importantes.
# -Wextra  : habilita avisos adicionais.
# -pedantic: reforça a conformidade com o padrão C.
# -O2      : aplica otimizações ao código.
CFLAGS = -Wall -Wextra -pedantic -O2

# Nome do executável gerado.
TARGET = testes_estruturas

# Arquivos-fonte que compõem o projeto.
SOURCES = main.c vetor.c ordenacao.c busca.c metricas.c estruturas.c

# Gera os nomes dos arquivos objeto correspondentes.
# Exemplo: main.c gera main.o.
OBJECTS = $(SOURCES:.c=.o)

# Regra padrão para gerar o executável.
all: $(TARGET)

# Vincula os arquivos objeto para criar o executável.
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regra genérica para transformar arquivos .c em .o.
# $< representa o arquivo-fonte.
# $@ representa o arquivo de saída.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove arquivos objeto e executáveis gerados.
clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET).exe

# Indica que all e clean não representam arquivos.
.PHONY: all clean

# TODO: Implementar geração automática de dependências
# entre arquivos .c e .h utilizando -MMD e -MP.
