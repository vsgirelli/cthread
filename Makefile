#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

# bibliotecas extras (tipo math.h) que forem adicionadas
# LIBS=

OBJS=bin/support.o bin/cutils.o bin/cthread.o

all: bin/cutils.o bin/cthread.o
	ar crs lib/libcthread.a $(OBJS)

bin/cutils.o: src/cutils.c
	gcc -m32 -c src/cutils.c -o bin/cutils.o -Wall

bin/cthread.o: src/cthread.c
	gcc -m32 -c src/cthread.c -o bin/cthread.o -Wall

clean:
	mv $(BIN_DIR)/support.o ../
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~
	mv ../support.o $(BIN_DIR)

tests:
	$(MAKE) -C testes

tests_clean:
	$(MAKE) -C testes clean
