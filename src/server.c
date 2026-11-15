#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"

int main()
{

    /*Déclarations */
    int f1, f2;
    Question q;
    Response r;

    /* Création des tubes nommés  */
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    /*initialisation du générateur de nombres aléatoires*/
    srand(getpid());

    /* Ouverture des tubes nommés  */
    f1 = open(FIFO1, O_RDONLY);
    if (f1 == -1)
    {
        perror("Erreur lors de l'ouverture du tube FIFO1");
        exit(1);
    }

    f2 = open(FIFO2, O_WRONLY);
    if (f2 == -1)
    {
        perror("Erreur lors de l'ouverture du tube FIFO2");
        exit(1);
    }

    printf("Serveur démarré et en attente de requêtes.\n");

    /* Installation des Handlers */
    signal(SIGUSR1, hand_reveil);
    signal(SIGINT, fin_serveur);
    signal(SIGTERM, fin_serveur);
    signal(SIGPIPE, SIG_IGN);

    while (1)
    {
        /* lecture d’une question */
        int size_q = sizeof(Question);
        ssize_t re = read(f1, &q, size_q);
        if (re > 0 && re == size_q)
        {
            printf("Traitement de la requête du client (PID : %d).\n", (int)q.pid_client);

            /* construction de la réponse */

            r.pid_client = q.pid_client;
            r.pid_server = getpid();
            for (int i = 0; i < q.n; i++)
            {
                r.tab[i] = rand() % 500;
            }
        }

        /* envoi de la réponse */
        client_finished = 0;
        write(f2, &r, sizeof(Response));

        /* envoi du signal SIGUSR1 au client concerné */
        kill(q.pid_client, SIGUSR1);

        /*Waiting Loop*/
        while (!client_finished)
        {
            pause();
        }
    }

    return 0;
}