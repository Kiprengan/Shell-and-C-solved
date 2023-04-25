#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define LISTEN_PORT 8080
#define MAX_CLIENTS 5

int main(int argc, char *argv[])
{ 
    int sock_listen, sock_recv;
    int i, addr_size, bytes_received;
    int incoming_len;
    int recv_msg_size;
    struct sockaddr_in my_addr, recv_addr;
    int select_ret;
    int max_fd;
    
    fd_set readfds;
    fd_set client_socks;

    struct timeval timeout={0,0}; 
    struct sockaddr remote_addr;
    
    char buf[BUF_SIZE];
    int client_sock[MAX_CLIENTS] = {0};
    int num_clients = 0;
    
    /* create socket for listening */
    sock_listen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_listen < 0)
    {
        printf("socket() failed\n");
        exit(0);
    }

    /* make local address structure */
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port = htons((unsigned short)LISTEN_PORT);
/* create socket for listening */
sock_listen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
if (sock_listen < 0)
{
    printf("socket() failed\n");
    exit(0);
}

/* make local address structure */
memset(&my_addr, 0, sizeof(my_addr));
my_addr.sin_family = AF_INET;
my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
my_addr.sin_port = htons((unsigned short)LISTEN_PORT);

/* bind socket to the local address */
i = bind(sock_listen, (struct sockaddr *) &my_addr, sizeof(my_addr));
if (i < 0)
{
    printf("bind() failed\n");
    exit(0);
}

/* listen */
i = listen(sock_listen, 5);
if (i < 0)
{
    printf("listen() failed\n");
    exit(0);
}

while (1)
{
    /* get new socket to receive data on */
    addr_size = sizeof(recv_addr);
    sock_recv = accept(sock_listen, (struct sockaddr *) &recv_addr, &addr_size);
    if (sock_recv < 0)
    {
        printf("accept() failed\n");
        exit(0);
    }

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(sock_recv, &readfds);

        select_ret = select(sock_recv + 1, &readfds, NULL, NULL, &timeout);

        if (select_ret == -1)
        {
            perror("select");
            exit(EXIT_FAILURE);
        }
        else if (select_ret == 0)
        {
            // No data received, do something else
        }
        else
        {
            /* data received from a client */
            bytes_received = recv(sock_recv, buf, BUF_SIZE, 0);
            buf[bytes_received] = 0;
            printf("Received: %s\n", buf);
            if (strcmp(buf, "shutdown") == 0)
                break;
        }
    }

    close(sock_recv);
}

close(sock_listen);
}
