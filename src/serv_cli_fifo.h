#ifndef SERV_CLI_FIFO_H
#define SERV_CLI_FIFO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#define NMAX 26
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

typedef struct{
    pid_t pid_client;
    int n;
} Question;


typedef struct {
    pid_t pid_client;
    pid_t pid_server;
    int tab[NMAX];
} Response;

#endif