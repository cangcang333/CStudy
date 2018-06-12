/*************************************************************************
	> File Name: event_active_good2.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 Jun 2018 08:32:46 AM CST
 ************************************************************************/

#include <stdio.h>
#include <event2/event.h>

struct event *ev;

static void cb(int sock, short which, void *arg)
{
    printf("In cb function\n");
    event_active(ev, EV_WRITE, 0);
    printf("Leave cb function\n");
}

int main(int argc, char **argv)
{
    struct event_config *cfg = event_config_new();
    /* Run at most 16 callbacks before checking for other events. */
    event_config_set_max_dispatch_interval(cfg, NULL, 16, 0);
    struct event_base *base = event_base_new_with_config(cfg);
    ev = event_new(base, -1, EV_PERSIST | EV_READ, cb, NULL);
    event_add(ev, NULL);
    event_active(ev, EV_WRITE, 0);
    event_base_loop(base, 0);

    return 0;
}

