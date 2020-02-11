//
// Created by joachim on 12.12.19.
//
// Functions related to the mesh gw
//

// needed for posix libs
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif

#include "LoRaMesh/mesh_gw.h"



// root node id
// TODO: vraiment besoin d'une table de routage? Pas uniquement besoin d'une seule entrée étant le root_node_id avec le next_hop?
// Oui, besoin d'une table de routage contenant les differentes routes possibles vers la rootGW (alternatives avec un metric; meshGW choisi la meilleure)
//routing_table_entry_t routing_table[MAX_ROUTING_TABLE_ENTRIES];
static routing_table_entry_t root_node = {0};

// Gateway node id
static uint64_t my_node_id = 0;


/**
 * Init with a route to the root gw (for testing purpose)
 * @param entry
 * @param my_id
 */
void init_mesh_gw(routing_table_entry_t *entry, uint64_t *my_id)
{
    printf("Lo-mesh gateway init with root_id=0x%.16llX and my_node_id=0x%.16llX\n", entry->dst_node_id, *my_id);
    root_node = *entry;
    my_node_id = *my_id;
}

/**
 * When mesh GW receives message from end device, forward to the root
 */
void forward_to_root(struct lgw_pkt_tx_s *txpkt, struct jit_queue_s *jit_queue)
{
    // check if root_node id is known
    if(root_node.dst_node_id == 0) {    // no route to the root node
        printf("No route to root node...\n");
        // TODO: route discovery with RREQ
    }
    else {                      // route to the root node id known
        // TODO: forward packet to next hop
        struct timeval current_unix_time;
        struct timeval current_concentrator_time;
        enum jit_error_e jit_result = JIT_ERROR_OK;
        enum jit_pkt_type_e downlink_type = JIT_PKT_TYPE_DOWNLINK_CLASS_C; //JIT_PKT_TYPE_DOWNLINK_CLASS_A;


#if 0   /* TODO: check TX parameter before trying to queue packet */
        if ((txpkt->freq_hz < tx_freq_min[txpkt->rf_chain]) || (txpkt->freq_hz > tx_freq_max[txpkt->rf_chain])) {
            jit_result = JIT_ERROR_TX_FREQ;
            MSG("ERROR: Packet REJECTED, unsupported frequency - %u (min:%u,max:%u)\n", txpkt->freq_hz, tx_freq_min[txpkt->rf_chain], tx_freq_max[txpkt->rf_chain]);
        }
        if (jit_result == JIT_ERROR_OK) {
            for (i=0; i<txlut.size; i++) {
                if (txlut.lut[i].rf_power == txpkt->rf_power) {
                    /* this RF power is supported, we can continue */
                    break;
                }
            }
            if (i == txlut.size) {
                /* this RF power is not supported */
                jit_result = JIT_ERROR_TX_POWER;
                MSG("ERROR: Packet REJECTED, unsupported RF power for TX - %d\n", txpkt->rf_power);
            }
        }
#endif

        /* insert packet to be sent into JIT queue */
        if (jit_result == JIT_ERROR_OK) {
            gettimeofday(&current_unix_time, NULL);
            get_concentrator_time(&current_concentrator_time, current_unix_time);

            jit_result = jit_enqueue(jit_queue, &current_concentrator_time, txpkt, downlink_type);
            if (jit_result != JIT_ERROR_OK) {
                printf("ERROR: Packet REJECTED (jit error=%d)\n", jit_result);
            }
        }
    }
}


void join_request_behavior(lorawan_packet_t *pkt, struct lgw_pkt_rx_s *p, struct jit_queue_s *jit_queue)
{
    struct lgw_pkt_tx_s txpkt;

    /* encapsulate packet and forward it to the root GW */
    // TODO: get link rf infos from the routing table?

    /* static filling the txpacket data */
    txpkt.freq_hz = (uint32_t) ((double)(1.0e6)*868.3);
    txpkt.rf_chain = 0;
    txpkt.rf_power = 14;
    txpkt.modulation = MOD_LORA;
    txpkt.datarate = DR_LORA_SF7;
    txpkt.bandwidth = BW_125KHZ;
    txpkt.coderate = CR_LORA_4_5;
    txpkt.preamble = 8;

#if 0    /* filling the txpacket from the rxpacket data */
    txpkt.freq_hz = p->freq_hz;
    txpkt.rf_chain = p->rf_chain;
    txpkt.rf_power = 14;
    txpkt.modulation = p->modulation;
    txpkt.datarate = p->datarate;
    txpkt.bandwidth = p->bandwidth;
    txpkt.coderate = p->coderate;
    txpkt.preamble = 8;
#endif

    /* encapsulate payload in mesh routing packet */
    uint8_t buff_index = 0;
    txpkt.payload[buff_index++] = 228;
    txpkt.payload[buff_index++] = DATA_PACKET << 5;
    // mesh data packet
    /*mesh_data_packet_t data_pkt = {
            .src_node_id = my_node_id,
            .dst_node_id = root_node.next_hop_id,
            .device_addr = 0,
            .payload = p->payload
    };*/
    //serialize_mesh_data_struct(txpkt.payload[buff_index], &data_pkt);     // TODO: implement method

    memcpy(&txpkt.payload[buff_index], p->payload, p->size);
    buff_index += p->size;
    // TODO: MIC?

    txpkt.size = buff_index+1;
    txpkt.tx_mode = IMMEDIATE; //TIMESTAMPED;

    forward_to_root(&txpkt, jit_queue);
}


//join_accept_behavior() { ... } ??
//data_behavior() { ... } ??