# Nome do executável final gerado
EXECUTABLE_NAME := bin/game

# Definindo as bibliotecas do Allegro necessárias para o projeto
ALLEGRO_LIBS := allegro-5 \
	allegro_main-5 \
	allegro_image-5 \
	allegro_font-5 \
	allegro_ttf-5 \
	allegro_audio-5 \
	allegro_acodec-5 \
	allegro_primitives-5

# Compilador utilizado
CC := gcc

# Variável para utilizar o pkg-config, que facilita o gerenciamento de bibliotecas
PKG_CONFIG := pkg-config

# Flags de compilação
# -g: Gera informações de depuração
# -Wall: Ativa todos os avisos (warnings)
# -MMD: Gera arquivos de dependências
# -Iinclude: Inclui o diretório 'include' no caminho de inclusão
# -Isrc/headers: Inclui o diretório 'src/headers' no caminho de inclusão
# `$(PKG_CONFIG) --cflags $(ALLEGRO_LIBS)`: Usa o pkg-config para obter as flags necessárias para as bibliotecas do Allegro
CFLAGS := -g -Wall -MMD -Iinclude -Isrc/headers `$(PKG_CONFIG) --cflags $(ALLEGRO_LIBS)`

# Obtém as bibliotecas do Allegro com pkg-config
LIBS := `$(PKG_CONFIG) --libs $(ALLEGRO_LIBS)`

# Arquivos de código-fonte e objetos
SOURCE_FILES := $(wildcard src/*.c)  # Obtém todos os arquivos .c no diretório src/
OBJECT_FILES := $(patsubst src/%, obj/%, $(SOURCE_FILES:.c=.o))  # Converte os arquivos de código-fonte em objetos, colocando-os na pasta obj/

# Arquivos de dependências
DEPENDENCY_FILES := $(OBJECT_FILES:.o=.d)

# Regra principal: gera o executável a partir dos arquivos objetos
$(EXECUTABLE_NAME): $(OBJECT_FILES)
	$(CC) $^ -o $(EXECUTABLE_NAME) $(LIBS)  # Compila os arquivos objetos e gera o executável final

# Regra para compilar os arquivos .c em objetos .o
obj/%.o: src/%.c
	@mkdir -p obj  # Cria o diretório obj se ele não existir
	$(CC) $(CFLAGS) -o $@ -c $<  # Compila cada arquivo .c individualmente

# Regra padrão para compilar tudo
all: $(EXECUTABLE_NAME)

# Regra para limpar os arquivos de compilação (objetos e executáveis)
clean:
	$(RM) -r obj $(EXECUTABLE_NAME)

# Regra para executar o programa após a compilação
run: $(EXECUTABLE_NAME)
	./$(EXECUTABLE_NAME)

# Inclui automaticamente os arquivos de dependências gerados durante a compilação
-include $(DEPENDENCY_FILES)

# Resumo:
# Este `Makefile` automatiza a compilação do projeto, gerenciando a construção dos arquivos
# .objeto a partir do código-fonte e linkando-os com as bibliotecas do Allegro para gerar o executável final.
# Ele também inclui regras para limpar os arquivos de compilação e rodar o jogo.
