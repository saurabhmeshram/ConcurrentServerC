/* Implementation for Server Side */
#include "common_head.h"

#define QLEN 5
#define MAX_CL 5

/* Server Network Address */
#define IP_ADDR "10.200.255.97"
#define PORT 5000

void *foo (void *arg);

/* Create Thread for each Client */
pthread_t cl_thread[MAX_CL];


int main (void)
{
    system("clear");
    printf("This is the Server\n");

    /* Select() related Calls */
    fd_set master;
    fd_set read_fds;
    int maxfd;

    int i, j = 0;
    int ret = -1, sock_fd, new_fd;
    int reuse_addr = 1;
    struct sockaddr_in serv, client;
    socklen_t slen = sizeof(struct sockaddr_in);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int));

    memset(&serv, 0, sizeof(struct sockaddr_in));
    memset(&client, 0, sizeof(struct sockaddr_in));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr(IP_ADDR);

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    /* Bind the fd with Server Strcuture */
    if(-1 == (ret = bind(sock_fd, (const struct sockaddr *) &serv, sizeof(struct sockaddr_in))))
    {
	printf("Error in Bind\n");
	exit (EXIT_FAILURE);
    }

    listen(sock_fd, QLEN);

    /* Add the listener to the master set */
    FD_SET(sock_fd, &master);
    maxfd = sock_fd;

    while(TRUE) 		/* Loop for Recving Conenctions from Clients */
    {
	read_fds = master;
	if (-1 == select(maxfd + 1, &read_fds, NULL, NULL, NULL))
	{
	    perror ("Select");
	    exit (EXIT_FAILURE);
	}

	for (i = 0; i <= maxfd; i++)
	{
	    if (FD_ISSET(i, &read_fds))
	    {
		if (i == sock_fd)
		{
		    /* To limit Maximum clients */
		    if (j >= (QLEN - 1))
		    {
			printf ("Maximum Client Limit reached\n");	
			exit (EXIT_FAILURE);
		    }
		    if (-1 == (new_fd = accept(sock_fd, (struct sockaddr *) &client, &slen)))
		    {
			perror ("accept");
			exit (EXIT_FAILURE);
		    } 
		    else {
			FD_SET (new_fd, &master);
			if (new_fd > maxfd)
			    maxfd = new_fd;

			printf("Connection From: [%s:%d][FD: %d]\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port), new_fd);

			/* Start New Thread - Specific to individual Client */
			pthread_create(&cl_thread[j], NULL, foo, (void *) &new_fd);
			j++; 
		    }
		}
	    }
	}
    } /* End for While(TRUE) */

    close(sock_fd);
    return 0;
}

void *foo (void *arg)
{
	int fd;
	fd = (*(int *)(arg));
	printf("Created Newthread [%ld] for Client fd : [%d]\n\n", pthread_self(), fd);

	char command [SIZE64] = {0};

	while (TRUE)
	{
	    read (fd, &command, SIZE64);
	    printf ("Msg from Client[%ld]: %s\n", pthread_self(), command);

	    write (fd, &command, strlen(command));
	    memset (&command, 0, SIZE64);
	}
	printf ("Exiting Thread :[%ld]\n", pthread_self());
	return NULL;
}
