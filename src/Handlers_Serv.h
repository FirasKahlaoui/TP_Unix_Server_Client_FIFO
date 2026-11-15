#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t client_finished = 0;

void hand_reveil(int sig)
{
    if (sig == SIGUSR1)
    {
        client_finished = 1;
    }
}

void fin_serveur(int sig)
{
    if (sig != SIGUSR1)
    {
        unlink(FIFO1);
        unlink(FIFO2);
        printf("أنهيت عملي");
        exit(0);
    }
}

#endif