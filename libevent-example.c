/*************************************************************************
	> File Name: libevent-example.c
	> Author: 
	> Mail: 
	> Created Time: Sat Jun  2 15:36:14 2018
 ************************************************************************/

#include <stdio.h>
#include <event.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct proto
{
    unsigned short len;
    char data[1024];
};

struct fd_state
{
    struct proto pdata;
    struct event read_event;
    struct event write_event;
    size_t nread;
    size_t nwrite;
};

void do_read(int fd, short events, void *data);
void do_write(int fd, short events, void *data);

struct fd_state *alloc_fd_state(struct event_base *base, int fd)
{
    struct fd_state *state;

    state = (struct fd_state *)malloc(sizeof(struct fd_state));
    if (!state)
        return state;

    /* Set handler for both read and write event, later can be invoked by event_add()  */
    event_set(&state->read_event, fd, EV_READ | EV_PERSIST, do_read, state);
    event_set(&state->write_event, fd, EV_WRITE | EV_PERSIST, do_write, state);
    state->nread = 0;
    state->nwrite = 0;

    return state;
}

void free_fd_state(struct fd_state *state)
{
    event_del(&state->read_event);
    free(state);
}

int set_nonblock(int fd)
{
    int flags;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return flags;

    if (flags & O_NONBLOCK)
    {
        flags &= ~O_NONBLOCK;
        return fcntl(fd, F_SETFL, flags);
    }

    return 0;
}

void do_read(int fd, short events, void *data)
{
    struct fd_state *state = (struct fd_state *)&data;
    struct proto pbuf;
    int ret;

    while (state->nread < sizeof(state->pdata))
    {
        ret = recv(fd, (char *)&state->pdata + state->nread, sizeof(state->pdata) - state->nread, 0);
        if (ret == -1)
        {
            if (errno != EAGAIN)
            {
                perror("read");
                free_fd_state(state);
                close(fd);
            }
            return ;
        }
        state->nread += ret;
    }

    /*
     * We complete with read, delete the event and set write event 
     * to echo back to the sender 
     */
    event_del(&state->write_event);
    event_add(&state->write_event, NULL);

    memcpy(&pbuf, &state->pdata, sizeof(pbuf));
    ret = ntohs(pbuf.len);

    if (ret >= sizeof(pbuf.data))
        pbuf.data[ret - 1] = '\0';
    else
        pbuf.data[ret] = '\0';

    fprintf(stderr, "%s\n", pbuf.data);
}

void do_write(int fd, short events, void *data)
{
    struct fd_state *state = (struct fd_state *)data;
    int ret;

    state->pdata.len = htons(state->pdata.len);

    while (state->nwrite < sizeof(state->pdata))
    {
        ret = send(fd, (char *)&state->pdata + state->nwrite, sizeof(state->pdata) - state->nwrite, 0);
        if (ret == -1)
        {
            if (errno != EAGAIN)
            {
                perror("write");
                free_fd_state(state);
                close(fd);
            }
            return ;
        }
        state->nwrite += ret;
    }

    /* Done with write, echo complete, cleanup... */
    event_del(&state->write_event);
    free_fd_state(state);
    close(fd);
}

void do_accept(int fd, short event, void *data)
{
    struct sockaddr_in addr;
    struct fd_state *state;
    socklen_t len = 0;
    int sock;

    sock = accept(fd, (struct sockaddr *)&addr, &len);
    if (sock == -1)
    {
        perror("accept");
        return ;
    }

    /* To meet asynchronously, socket must be set to nonblocking */
    if (set_nonblock(sock) == -1)
    {
        perror("set_nonblock");
        close(sock);
        return ;
    }

    /* Allocate and initialize fd state for incoming event */
    state = alloc_fd_state((struct event_base *)data, sock);
    assert(state);
    event_add(&state->read_event, NULL);
}

int main(int argc, char **argv)
{
    int ssock, opt, ret;
    unsigned int port;
    struct sockaddr_in saddr;
    struct event_base *evbase;
    struct event ev;

    if (argc < 2)
    {
        fprintf(stderr, "Usage %s [port]\n", *argv);
        return 1;
    }

    ret = atoi(argv[1]);
    if (ret <= 0)
    {
        fprintf(stderr, "Invalid port: %s\n", argv[1]);
        return 1;
    }

    port = ret;

    ssock = socket(AF_INET, SOCK_STREAM, 0);
    if (ssock == -1)
    {
        perror("socket");
        return 1;
    }

    ret = set_nonblock(ssock);
    if (ret == -1)
    {
        perror("set_nonblock");
        return 1;
    }

    opt = 1;
    ret = setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    if (ret == -1)
    {
        perror("setsockopt");
        close(ssock);
        return 1;
    }

    memset(&saddr, 0, sizeof(struct sockaddr_in));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("bind");
        close(ssock);
        return 1;
    }

    ret = listen(ssock, 10);
    if (ret == -1)
    {
        perror("listen");
        close(ssock);
        return 1;
    }

    /* libevent library initialization */
    evbase = event_init();
    if (!evbase)
    {
        fprintf(stderr, "Could not init libevent\n");
        close(ssock);
        return 1;
    }

    /* First we install read event for accept() to the listener */
    event_set(&ev, ssock, EV_READ | EV_PERSIST, do_accept, evbase);
    event_add(&ev, NULL);
    event_base_dispatch(evbase);


    return 0;
}


