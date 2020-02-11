//
// Created by joachim on 12.12.19.
//
// Functions related to the root gw
//

#ifndef ROOT_GATEWAY_ROOT_GW_H
#define ROOT_GATEWAY_ROOT_GW_H

#include <stdint.h>         /* C99 types */
#include <stdbool.h>        /* bool type */
#include "lora_mesh.h"


void init_root_gw(uint64_t *my_id);

#endif //ROOT_GATEWAY_ROOT_GW_H
