# Makefile para geração de programas teste

CC=gcc
LIB_DIR=../lib

all: testev teste0 teste1 teste2 teste3 teste4 teste5 teste6 teste7

testev: testev.c $(LIB_DIR)/libcthread.a
	$(CC) -o testev testev.c -L$(LIB_DIR) -lcthread -Wall

teste0: teste0.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste0 teste0.c -L$(LIB_DIR) -lcthread -Wall

teste1: teste1.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste1 teste1.c -L$(LIB_DIR) -lcthread -Wall

teste2: teste2.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste2 teste2.c -L$(LIB_DIR) -lcthread -Wall

teste3: teste3.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste3 teste3.c -L$(LIB_DIR) -lcthread -Wall

teste4: teste4.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste4 teste4.c -L$(LIB_DIR) -lcthread -Wall

teste5: teste5.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste5 teste5.c -L$(LIB_DIR) -lcthread -Wall

teste6: teste6.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste6 teste6.c -L$(LIB_DIR) -lcthread -Wall

teste7: teste7.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste7 teste7.c -L$(LIB_DIR) -lcthread -Wall

clean:
	rm -rf testev teste0 teste1 teste2 teste3 teste4 teste5 teste6 teste7
	rm -rf teste?.o *~ *log
