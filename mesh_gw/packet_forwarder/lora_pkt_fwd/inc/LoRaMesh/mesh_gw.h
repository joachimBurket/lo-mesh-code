//
// Created by joachim on 12.12.19.
//
// Functions related to the mesh gw
//

#ifndef MESH_GATEWAY_MESH_GW_H
#define MESH_GATEWAY_MESH_GW_H

#include <stdint.h>         /* C99 types */
#include <stdbool.h>        /* bool type */
#include <stdio.h>          /* printf, fprintf, snprintf, fopen, fputs */
#include <string.h>         /* memset */

#include <time.h>           /* time, clock_gettime, strftime, gmtime */
#include <sys/time.h>       /* timeval */

#include "jitqueue.h"
#include "timersync.h"
#include "loragw_hal.h"
#include "lora_mesh.h"

void init_mesh_gw(routing_table_entry_t *entry, uint64_t *my_id);
void join_request_behavior(lorawan_packet_t *pkt, struct lgw_pkt_rx_s *p, struct jit_queue_s *jit_queue);

#endif //MESH_GATEWAY_MESH_GW_H
