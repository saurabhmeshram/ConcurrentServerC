#include "common_head.h"

int init_connection(struct sockaddr_in *client, char **arr);
int stop_connection(int fd);

/* 
Description: Init a Connection to the FTP Server.
Return: Socket FD of the client 
 */
int init_connection(struct sockaddr_in *client, char **arr)
{
    /* Create Socket for Client */
    int sock_fd = -1;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Created Socket, Sock_fd is [%d]\n", sock_fd);

    memset(client, 0, sizeof(struct sockaddr_in));

    client->sin_family = AF_INET;
    client->sin_addr.s_addr = inet_addr(arr[1]);
    client->sin_port = htons(atoi(arr[2]));

    printf("Connecting...\n");
    if (-1 == (connect(sock_fd, (struct sockaddr *)client, sizeof(struct sockaddr_in))))
    {
	perror ("Connect");
	exit(EXIT_FAILURE);
    }
    return sock_fd;
}

int stop_connection(int fd)
{
    close(fd);
    return TRUE;
}

int main(int argc, char **argv)
{
    system("clear");
    if (1 == argc) {
	printf("Usage : <%s> <IP_ADDRESS> <PORT>\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    int sock_fd = -1;
    struct sockaddr_in client;
    char quit = 1;

    char *command = malloc (64 * sizeof(char));

    sock_fd = init_connection(&client, argv);
    printf("Recvd Sockfd as [%d]\n", sock_fd);


    do {
#if 1
	printf("send :$ ");
	fgets(command, 64, stdin);
	command[strlen(command) - 1] = '\0';

	/* Do Nothing if input is new line */
	if (command[0] == 10) {
	    printf("Newline");
	    break;
	}
	
	write (sock_fd, command, strlen(command));
	memset (command, 0, 64);

	read (sock_fd, command, 64);
	printf ("Echo: %s\n", command);
	memset (command, 0, 64);

#endif
    } while(1 == quit);

    free(command);
    stop_connection(sock_fd);
    return 0;
}
