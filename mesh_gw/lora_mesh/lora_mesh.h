//
// Created by joachim on 07.11.19.
//

#ifndef LORA_MESH_H
#define LORA_MESH_H

#include <stdint.h>        /* C99 types */
#include <stdbool.h>    /* bool type */

/** RREQ packet structure */
struct rreq_packet {
    uint8_t hop_count;
    uint8_t rreq_id;
    uint8_t dst_node_id[6];
    uint8_t dst_seq_no;
    uint8_t src_node_id[6];
    uint8_t src_seq_no;
    uint8_t prev_hop_id[6];
};

/** RREP packet structure */
struct rreq_packet {
    uint8_t hop_count;
    uint8_t dst_node_id[6];
    uint8_t dst_seq_no;
    uint8_t src_node_id[6];
    uint8_t prev_hop_id[6];
};

/** RRER packet structure */
struct rrer_packet {
    uint8_t dst_count;
    uint8_t unreachable_node_id[6];
    uint8_t dst_seq_no;
};

/** data packet structure */
struct data_packet {
    uint8_t dst_node_id[6];
    uint8_t src_node_id[6];
    uint8_t device_addr[4];
    uint8_t payload[256];
};


/** Routing table entry structure */
struct routing_table_entry {
    uint8_t dst_node_id[6];
    uint8_t next_hop_id[6];
    uint8_t dst_seq_no;
    uint8_t hop_count;
};

/** Device table entry structure */
struct device_table_entry {
    uint8_t device_addr[4];
    uint8_t dst_node_id[6];     /* For downlink forward */
};


#endif //LORA_MESH_H
