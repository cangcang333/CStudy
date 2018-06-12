/*************************************************************************
	> File Name: tcp_client.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 Jun 2018 07:22:41 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LISTEN_BACKLOG  50
#define BUF_SIZE  1024

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    int listenSfd, connFd;
    int nread;
    int ret = -1;
    int reuseAddr = 1;
    struct sockaddr_in addr_sin ;
    struct sockaddr_in peer_addr_sin ;
    unsigned int addrlen;
    char *peerIP;
    long peerPort;
    char buf[BUF_SIZE];

    listenSfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSfd < 0)
        handle_error("socket");

    memset(&addr_sin, 0, sizeof(struct sockaddr_in));
    addr_sin.sin_family = AF_INET;
    addr_sin.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_sin.sin_port = htons(12345);    /* WARN: This place can not use htonl(12345) */
    addrlen = sizeof(addr_sin);
    printf("addrlen is %d\n", addrlen);

    ret = setsockopt(listenSfd, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr));
    if (ret < 0)
        handle_error("setsockopt");

    ret = bind(listenSfd, (struct sockaddr *)&addr_sin, sizeof(addr_sin));
    if (ret < 0)
        handle_error("bind");

    ret = listen(listenSfd, LISTEN_BACKLOG);
    if (ret < 0)
        handle_error("listen");
    printf("listening ...\n");
    
    while (1)
    {
        ret = accept(listenSfd, (struct sockaddr *) &addr_sin, &addrlen);
        if (ret > 0)
        {
            connFd = ret;
            printf("connFd is %d\n", connFd);
            /* getpeername */
            ret = getpeername(connFd, (struct sockaddr *) & peer_addr_sin, &addrlen);
            if (ret < 0)
                handle_error("getpeername");

            peerIP = inet_ntoa(peer_addr_sin.sin_addr);
            peerPort = ntohs(peer_addr_sin.sin_port);
            printf("peerIP is %s and peerPort is %ld\n", peerIP, peerPort);

            nread = read(connFd, buf, BUF_SIZE);
            if (ret > 0)
            {
                printf("read %d bytes, buf is %s\n", nread, buf);
            }
        }    
        else
        {
            handle_error("accept");
        }
    }

    return 0;
}

