#ifndef HANDLERS_CLI_H
#define HANDLERS_CLI_H

#include <signal.h>

volatile sig_atomic_t server_ready = 0;

void hand_reveil(int sig){

    server_ready = 1;

}

#endif