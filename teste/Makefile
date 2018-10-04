# Makefile para geração de programas teste

CC=gcc
LIB_DIR=../lib

all: prio cyeldSamePrio teste5 teste6 

prio: prio.c $(LIB_DIR)/libcthread.a
	$(CC) -o prio prio.c -L$(LIB_DIR) -lcthread -Wall

cyeldSamePrio: cyeldSamePrio.c $(LIB_DIR)/libcthread.a
	$(CC) -o cyeldSamePrio cyeldSamePrio.c -L$(LIB_DIR) -lcthread -Wall

teste5: teste5.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste5 teste5.c -L$(LIB_DIR) -lcthread -Wall

teste6: teste6.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste6 teste6.c -L$(LIB_DIR) -lcthread -Wall

clean:
	rm -rf prio cyeldSamePrio teste5 teste6
	rm -rf teste?.o *~ *log
