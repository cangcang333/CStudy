/*************************************************************************
	> File Name: bufferevent_test1.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 Jun 2018 03:59:32 PM CST
 ************************************************************************/

#include <stdio.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <sys/socket.h>
#include <string.h>

void eventCb(struct bufferevent *bev, short events, void *ptr)
{
    if (events & BEV_EVENT_CONNECTED)
    {
        /* We're connected to 127.0.0.1:8080. Ordinarily we'd do
        * something here, like start reading or writing. */
        printf("Got connected\n");
    }
    else if (events & BEV_EVENT_ERROR)
    {
        /* An error occured while connecting */
        printf("Got an error while connecting\n");
    }
}

int main_loop(void)
{
    struct event_base *base;
    struct bufferevent *bev;
    struct sockaddr_in sin;

    base = event_base_new();

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(0x7f000001);    /* 127.0.0.1 */
    sin.sin_port = htons(8080);                 /* Port 8080 */

    bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, NULL, NULL, eventCb, NULL);

    if (bufferevent_socket_connect(bev, (struct sockaddr *)&sin, sizeof(sin) < 0))
    {
        /* Error starting connection */
        bufferevent_free(bev);
        return -1;
    }

    event_base_dispatch(base);

    return 0;
}

int main(int argc, char **argv)
{
    main_loop();

    return 0;
}

