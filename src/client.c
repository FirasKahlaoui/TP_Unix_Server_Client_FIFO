#include <serv_cli_fifo.h>
#include <Handlers_Cli.h>

int main(){

    /* Déclarations */ 
    int f1, f2;
    Question q;
    Response r;
    pid_t id = getpid();
    /* Ouverture des tubes nommés  */ 
    f1 = open(FIFO1, O_WRONLY);
    if (f1 == -1)
    {
        perror("Mat7alech ya M3alem");
        exit(1);
    }

    f2 = open(FIFO2, O_RDONLY);
    if (f2 == -1)
    {
        perror("Mat7alech ya M3alem zouz");
        exit(1);
    }
    /* Installation des Handlers */ 
    signal(SIGUSR1, hand_reveil);

    /* Construction et envoi d’une question */ 
    q.pid_client = getpid();
    q.n = (rand() % NMAX) + 1;

    write(f1, &q, sizeof(Question));
    printf("Wosletek el 9adhya??");

    /* Attente de la réponse */ 
    while (server_ready == 0)
    {
        pause();
    }
    
    /* Lecture de la réponse */ 

    do
    {
        read(f2, &r, sizeof(Response));
    } while (r.pid_client != id);


    /* Envoi du signal SIGUSR1 au serveur */ 

    kill(r.pid_server, SIGUSR1);

    /* Traitement local de la réponse */ 
    printf("Aka el 9adhya wolset yar7em waldik!!!");
    for (int j = 0; j < q.n; j++){
        printf("El 9adhya noumrou %d : %d",j+1,r.tab[j]);
    }


    close(f1);
    close(f2);

    return 0;
}