#include "Handlers_Cli.h"
#include "serv_cli_fifo.h"

int main()
{

    /* Déclarations */
    int f1, f2;
    Question q;
    Response r;
    pid_t id = getpid();
    printf("PID du client : %d\n", (int)id);
    /*initialisation du générateur de nombres aléatoires*/
    srand(getpid());
    /* Ouverture des tubes nommés  */
    f1 = open(FIFO1, O_WRONLY);
    if (f1 == -1)
    {
        perror("Erreur lors de l'ouverture du tube FIFO1");
        exit(1);
    }
    f2 = open(FIFO2, O_RDONLY);
    if (f2 == -1)
    {
        perror("Erreur lors de l'ouverture du tube FIFO2");
        exit(1);
    }
    /* Installation des Handlers */
    signal(SIGUSR1, hand_reveil);

    /* Construction et envoi d’une question */
    q.pid_client = getpid();
    q.n = (rand() % NMAX) + 1;

    write(f1, &q, sizeof(Question));
    printf("Demande envoyée au serveur pour générer %d nombres.\n", q.n);

    /* Attente de la réponse */
    while (!server_ready)
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
    printf("Réponse reçue du serveur.\n");
    printf("PID client dans la réponse : %d\n", (int)r.pid_client);
    for (int j = 0; j < q.n; j++)
    {
        printf("Nombre %d : %d\n", j + 1, r.tab[j]);
    }

    close(f1);
    close(f2);

    return 0;
}