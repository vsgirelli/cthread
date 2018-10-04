# Makefile para geração de programas teste

CC=gcc
LIB_DIR=../lib

all: prio cyeldSamePrio teste cjoinTest testingSemaphore testingloops joiningAlreadyJoinedThread

prio: prio.c $(LIB_DIR)/libcthread.a
	$(CC) -o prio prio.c -L$(LIB_DIR) -lcthread -Wall

cyeldSamePrio: cyeldSamePrio.c $(LIB_DIR)/libcthread.a
	$(CC) -o cyeldSamePrio cyeldSamePrio.c -L$(LIB_DIR) -lcthread -Wall

teste: teste.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste teste.c -L$(LIB_DIR) -lcthread -Wall

cjoinTest: cjoinTest.c $(LIB_DIR)/libcthread.a
	$(CC) -o cjoinTest cjoinTest.c -L$(LIB_DIR) -lcthread -Wall

testingSemaphore: testingSemaphore.c $(LIB_DIR)/libcthread.a
	$(CC) -o testingSemaphore testingSemaphore.c -L$(LIB_DIR) -lcthread -Wall

testingloops: testingloops.c $(LIB_DIR)/libcthread.a
	$(CC) -o testingloops testingloops.c -L$(LIB_DIR) -lcthread -Wall

joiningAlreadyJoinedThread: joiningAlreadyJoinedThread.c $(LIB_DIR)/libcthread.a
	$(CC) -o joiningAlreadyJoinedThread joiningAlreadyJoinedThread.c -L$(LIB_DIR) -lcthread -Wall

clean:
	rm -rf prio cyeldSamePrio teste cjoinTest testingSemaphore testingloops joiningAlreadyJoinedThread
	rm -rf teste?.o *~ *log
