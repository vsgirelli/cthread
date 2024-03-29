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

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

# bibliotecas extras (tipo math.h) que forem adicionadas
# LIBS=

OBJS=$(BIN_DIR)/support.o $(BIN_DIR)/cutils.o $(BIN_DIR)/cthread.o

all: cutils cthread
	ar crs $(LIB_DIR)/libcthread.a $(OBJS)

cutils: $(SRC_DIR)/cutils.c
	gcc -c $(SRC_DIR)/cutils.c -o $(BIN_DIR)/cutils.o -Wall

cthread: $(SRC_DIR)/cthread.c
	gcc -c $(SRC_DIR)/cthread.c -o $(BIN_DIR)/cthread.o -Wall

clean:
	mv $(BIN_DIR)/support.o ../
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~
	mv ../support.o $(BIN_DIR)
