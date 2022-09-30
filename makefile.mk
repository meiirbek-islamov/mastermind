a.out : client.o mastermind.o gcc
	client.o mastermind.o client.o : client.o server.h	gcc
	- c client.c mastermind.o : mastermind.o server.h gcc
	- c mastermind.c
