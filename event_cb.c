/*************************************************************************
	> File Name: event_cb.c
	> Author: 
	> Mail: 
	> Created Time: Mon 11 Jun 2018 11:33:45 AM CST
 ************************************************************************/

#include <stdio.h>
#include <event2/event.h>

static int n_calls = 0;

void cb_func(evutil_socket_t fd, short what, void *arg)
{
    struct event *me = arg;
    printf("cb_func called %d times so far.\n", ++n_calls);
    if (n_calls > 100)
        event_del(me);
}

void run(struct event_base *base)
{
    struct timeval one_sec = {1, 0};
    struct event *ev;
    /* We're going to set up a repeating timer to get called 100 times */
    /* The event_self_cbarg() functions was introduced in Libevent 2.1.1-alpha. */
    ev = event_new(base, -1, EV_PERSIST, cb_func, event_self_cbarg());
    event_add(ev, &one_sec);
    event_base_dispatch(base);
}

int main(int argc, char *argv[])
{
    struct event_base *base = NULL;
    run(base);

    return 0;
}

