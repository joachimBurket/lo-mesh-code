//
// Created by joachim on 14.11.19.
//
// Contains the basics of lora-mesh protocol
//

#ifndef LORA_MESH_H
#define LORA_MESH_H

#include <stdint.h>         /* C99 types */
#include <stdbool.h>        /* bool type */


#define NODE_ID_SIZE                6           /* Size in Bytes of a node id */
#define DEV_ADDR_SIZE               4           /* Size in Bytes of the device address */
#define EUI_SIZE                    8           /* Size in Bytes of the DEV_EUI and APP_EUI */
#define MAX_ROUTING_TABLE_ENTRIES   32
#define MAX_DEVICE_TABLE_ENTRIES    128

/** Struct containing LoRa packet useful fields of the headers */
typedef struct lorawan_packet {
    uint8_t mtype;
    uint8_t rfu;
    uint64_t app_eui;
    uint64_t dev_eui;
    uint32_t dev_addr;
    uint8_t fctrl;
    uint16_t fcnt;
    uint8_t *payload;
    // size?
}lorawan_packet_t;

/** Mesh packet type enum */
enum mesh_packet_type {
    DATA_PACKET = 0,
    RREQ_PACKET,
    RREP_PACKET,
    RRER_PACKET
};

/** RREQ packet structure */
typedef struct mesh_rreq_packet {
    uint8_t hop_count;
    uint8_t rreq_id;
    uint64_t dst_node_id;
    uint8_t dst_seq_no;
    uint64_t src_node_id;
    uint8_t src_seq_no;
    uint64_t prev_hop_id;
}mesh_rreq_packet_t;

/** RREP packet structure */
typedef struct mesh_rrep_packet {
    uint8_t hop_count;
    uint64_t dst_node_id;
    uint8_t dst_seq_no;
    uint64_t src_node_id;
    uint64_t prev_hop_id;
}mesh_rrep_packet_t;

/** RRER packet structure */
typedef struct mesh_rrer_packet {
    uint8_t dst_count;
    uint64_t unreachable_node_id;
    uint8_t dst_seq_no;
}mesh_rrer_packet_t;

/** data packet structure */
typedef struct mesh_data_packet {
    uint64_t dst_node_id;
    uint64_t src_node_id;
    uint32_t device_addr;
    uint8_t size;
    uint8_t payload[256];
}mesh_data_packet_t;


// TODO: Add metrics of the link between this GW and the next hop (or a device)?
//   - rf_power, freq_hz, modulation, datarate (SF), bandwidth, coderate, preamble

/* Routing table entry structure */
typedef struct routing_table_entry {
    uint64_t dst_node_id;
    uint64_t next_hop_id;
    uint8_t dst_seq_no;
    uint8_t hop_count;
    bool valid;
}routing_table_entry_t;

/* Routing table */
//typedef struct routing_table {
//    routing_table_entry_t entries[MAX_ROUTING_TABLE_ENTRIES];
//
//} routing_table;

/* Device table entry structure */      // TODO: Add a timestamp to each entry, to invalidate it after a while?
typedef struct device_table_entry {
    uint32_t device_addr;
    uint64_t dst_node_id;     /* For downlink forward */
    bool valid;
}device_table_entry_t;

/* Device table */
//typedef struct device_table {
//    device_table_entry_t entries[MAX_DEVICE_TABLE_ENTRIES];
//
//} device_table;


void fill_lorawan_pkt_struct(uint8_t *lora_payload, uint16_t size, lorawan_packet_t *pkt);
void fill_mesh_data_struct(uint8_t *mesh_payload, uint16_t size, mesh_data_packet_t *pkt);
void fill_mesh_rreq_struct(uint8_t *mesh_payload, uint16_t size, mesh_rreq_packet_t *pkt);
void fill_mesh_rrep_struct(uint8_t *mesh_payload, uint16_t size, mesh_rrep_packet_t *pkt);
void fill_mesh_rrer_struct(uint8_t *mesh_payload, uint16_t size, mesh_rrer_packet_t *pkt);

#endif //LORA_MESH_H
