/*************************************************************************
	> File Name: event_priority_test.c
	> Author: 
	> Mail: 
	> Created Time: Mon 11 Jun 2018 02:37:01 PM CST
 ************************************************************************/

#include <stdio.h>
#include <event2/event.h>

void read_cb(evutil_socket_t, short, void *);
void write_cb(evutil_socket_t, short, void *);

void read_cb(evutil_socket_t fd, short what, void *arg)
{

}

void write_cb(evutil_socket_t fd, short what, void *arg)
{

}

void main_loop(evutil_socket_t fd)
{
    struct event *important, *unimportant;
    struct event_base *base;

    base = event_base_new();
    event_base_priority_init(base, 2);
    /* Now base has priority 0 and priority 1 */
    important = event_new(base, fd, EV_WRITE|EV_PERSIST, write_cb, NULL);
    unimportant = event_new(base, fd, EV_READ|EV_PERSIST, read_cb, NULL);
    event_priority_set(important, 0);
    event_priority_set(unimportant, 1);

    /* Now, whenever the fd is ready for writing, the write callback will
     * happen before the read callback. The read callback won't happen at 
     * all until the write callbackis no longer active. 
     */
}

int main(int argc, char **argv)
{
    
    return 0;
}

