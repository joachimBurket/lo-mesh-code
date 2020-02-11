//
// Created by joachim on 12.12.19.
//
// Functions related to the root gw
//

// needed for posix libs
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif

#include "root_gw.h"
#include <stdio.h>          /* printf, fprintf, snprintf, fopen, fputs */
#include <string.h>         /* memset */

#include <time.h>           /* time, clock_gettime, strftime, gmtime */
#include <sys/time.h>       /* timeval */

#include "jitqueue.h"
#include "timersync.h"
#include "loragw_hal.h"

// Gateway node id
static uint64_t my_node_id = 0;


// Init with a route to the root gw (for testing purpose)
void init_root_gw(uint64_t *my_id)
{
    printf("Lo-mesh root gateway init with my_node_id=0x%.16llX\n", *my_id);
    my_node_id = *my_id;
}




//join_accept_behavior() { ... } ??
//data_behavior() { ... } ??


