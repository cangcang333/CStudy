/*************************************************************************
	> File Name: tcp_client.c
	> Author: 
	> Mail: 
	> Created Time: 四  6/14 15:35:28 2018
 ************************************************************************/

#include <stdio.h>
/* for EXIT_FAILURE */
#include <stdlib.h>
/* for socket() */
#include <sys/socket.h>
/* for bzero() */
#include <string.h>
/* for inet_pton() */
#include <arpa/inet.h>
/* for read() */
#include <unistd.h>

#define MAXBUFSIZE 4096

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    int sockfd, n, ret;
    char recvBuff[MAXBUFSIZE + 1];
    struct sockaddr_in servaddr;

    printf("argc = %d\n", argc);
    if (argc != 3)
        handle_error("usage: a.out <IPaddress>");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        handle_error("socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton error for %s\n", argv[1]);
        handle_error("inet_pton");
    }

    ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (ret < 0)
        handle_error("connect");
    printf("After connect, sockfd = %d\n", sockfd);

    /* Read data from the socket and print it to stdout */
    while ( (n = read(sockfd, recvBuff, MAXBUFSIZE)) > 0 )
    {
        printf("read %d bytes\n", n);
        recvBuff[n] = '\0';    /* null terminator */
        if (fputs(recvBuff, stdout) == EOF)
            handle_error("fputs");
    }
    if (n < 0)
        handle_error("read");



    return 0;
}
