/*************************************************************************
	> File Name: event_active_bad.c
	> Author: 
	> Mail: 
	> Created Time: Mon 11 Jun 2018 03:24:19 PM CST
 ************************************************************************/

#include <stdio.h>
#include <event2/event.h>

struct event *ev;

static void cb(int sock, short which, void *arg)
{
    /* Whoops: Calling event_active on the same event unconditionally
    * from within its callback means that no other events might not get run! */
    printf("In cb function\n");
//    event_active(ev, EV_WRITE, 0);
    printf("Leaving cb function\n");
}

int main(int argc, char **argv)
{
    printf("In main function\n");
    struct event_base *base = event_base_new();
    ev = event_new(base, -1, EV_PERSIST | EV_READ, cb, NULL);
    event_add(ev, NULL);
    event_active(ev, EV_WRITE, 0);
    event_base_loop(base, 0);

    printf("Returning\n");

    return 0;
}

