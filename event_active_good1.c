/*************************************************************************
	> File Name: event_active_good1.c
	> Author: 
	> Mail: 
	> Created Time: Mon 11 Jun 2018 03:53:16 PM CST
 ************************************************************************/

#include <stdio.h>
#include <event2/event.h>

struct event *ev;
struct timeval tv;

static void cb(int sock, short which, void *arg)
{
    printf("In cb function\n");
    if (!evtimer_pending(ev, NULL))
    {
        event_del(ev);
        evtimer_add(ev, &tv);
    }
    printf("Leave cb function\n");
}

int main(int argc, char **argv)
{
    printf("In main function\n");
    struct event_base *base = event_base_new();
    
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    ev = evtimer_new(base, cb, NULL);
    evtimer_add(ev, &tv);
    event_base_loop(base, 0);
    printf("Leave main function\n");

    return 0;
}

