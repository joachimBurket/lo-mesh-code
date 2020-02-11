//
// Created by joachim on 14.11.19.
//
// Contains the basics of lora-mesh protocol
//

// needed for posix libs
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif

#include <stdint.h>         /* C99 types */
#include <stdio.h>          /* printf, fprintf, snprintf, fopen, fputs */
#include <string.h>         /* memset */

#include <time.h>           /* time, clock_gettime, strftime, gmtime */
#include <sys/time.h>       /* timeval */

#include "jitqueue.h"
#include "timersync.h"
#include "loragw_hal.h"

#include "LoRaMesh/lora_mesh.h"


// routing and devices tables
static device_table_entry_t device_table[MAX_DEVICE_TABLE_ENTRIES];


void fill_lorawan_pkt_struct(uint8_t *lora_payload, uint16_t size, lorawan_packet_t *pkt)
{
    uint8_t mac_header = lora_payload[0];
    pkt->mtype = (mac_header & 0xE0) >> 5;
    pkt->rfu = (mac_header & 0x1C) >> 2;

    printf("   PHY payload :\n   ");
    for(int i = 0; i < size; i++) {
        printf("%.2X", lora_payload[i]);
    }
    printf("\n   MAC header=0x%.2X; MHDR->Mtype=%d; MHDR->RFU=%d\n", mac_header, pkt->mtype, pkt->rfu);

    /* Getting the packet informations depending on the packet type */
    switch (pkt->mtype) {
        case 0:     // join request
            for(int i = 1; i <=8 ; i++) {
                pkt->app_eui |= (unsigned long long) lora_payload[i] << ((i-1)*8);
            }
            for(int i = 9; i <=16 ; i++) {
                pkt->dev_eui |= (unsigned long long) lora_payload[i] << ((i-9)*8);
            }
            printf("   Mtype = Join Request: app_eui=0x%.16llX, dev_eui=0x%.16llX\n", pkt->app_eui, pkt->dev_eui);

            break;
        case 1:     // Join accept
            pkt->dev_addr  = lora_payload[6];
            pkt->dev_addr |= lora_payload[7] << 8;
            pkt->dev_addr |= lora_payload[8] << 16;
            pkt->dev_addr |= lora_payload[9] << 24;
            printf("   Join Accept: dev_addr=0x%.08X\n", pkt->dev_addr);
            break;
        case 2:     // Unconfirmed data up
        case 3:     // Unconfirmed data down
        case 4:     // Confirmed data up
        case 5:     // Confirmed data down
            // FHDR - DevAddr
            pkt->dev_addr  = lora_payload[1];
            pkt->dev_addr |= lora_payload[2] << 8;
            pkt->dev_addr |= lora_payload[3] << 16;
            pkt->dev_addr |= lora_payload[4] << 24;
            // FHDR - FCnt
            pkt->fcnt  = lora_payload[6];
            pkt->fcnt |= lora_payload[7] << 8;

            printf( "   Data Packet: dev_addr=0x%08X (fcnt=%u)\n", pkt->dev_addr, pkt->fcnt );

            break;
        case 7:     // Propretary: a mesh routing packet
            break;
        default:
            break;
    }
}


/**
 *
 * @param mesh_payload      Only mesh packet payload
 * @param size              Size of the mesh packet payload
 * @param pkt               Struct to fill with payload values
 */
void fill_mesh_data_struct(uint8_t *mesh_payload, uint16_t size, mesh_data_packet_t *pkt)
{
    uint8_t  buff_index = 0;

    // clear the structure
    memset(pkt, 0, sizeof(mesh_data_packet_t));

    // fill the destination/source nodes id
    for(int i = 0; i < NODE_ID_SIZE; i++) {
        pkt->dst_node_id |= (unsigned long long) mesh_payload[i] << i*8;
        pkt->src_node_id |= (unsigned long long) mesh_payload[NODE_ID_SIZE+i] << i*8;
    }
    buff_index += (2*NODE_ID_SIZE);

    // fill the device address
    for(int i = 0; i < DEV_ADDR_SIZE; i++) {
        pkt->device_addr |= mesh_payload[buff_index + i] << i*8;
    }
    buff_index += DEV_ADDR_SIZE;

    // fill the data payload
    memcpy(pkt->payload, &mesh_payload[buff_index], sizeof(pkt->payload)-1);

    printf("dst_node_id=0x%.16llX; src_node_id=0x%.16llX; device_addr=0x%08X\n", pkt->dst_node_id, pkt->src_node_id, pkt->device_addr);
}

void serialize_mesh_data_struct(uint8_t *mesh_payload, mesh_data_packet_t *pkt)
{
    uint8_t  buff_index = 0;


}


/**
 *
 * @param mesh_payload      Only mesh packet payload
 * @param size              Size of the mesh packet payload
 * @param pkt               Struct to fill with payload values
 */
void fill_mesh_rreq_struct(uint8_t *mesh_payload, uint16_t size, mesh_rreq_packet_t *pkt)
{
    uint8_t  buff_index = 0;

    pkt->hop_count = mesh_payload[buff_index++];
    pkt->rreq_id = mesh_payload[buff_index++];

    // fill the destination nodes id
    for(int i = 0; i < NODE_ID_SIZE; i++) {
        pkt->dst_node_id |= (unsigned long long) mesh_payload[buff_index++] << i*8;
    }
    pkt->dst_seq_no = mesh_payload[buff_index++];

    // fill the source nodes id
    for(int i = 0; i < NODE_ID_SIZE; i++) {
        pkt->src_node_id |= (unsigned long long) mesh_payload[buff_index++] << i*8;
    }
    pkt->src_seq_no = mesh_payload[buff_index++];

    // fill the previous hop node id
    for(int i = 0; i < NODE_ID_SIZE; i++) {
        pkt->prev_hop_id |= (unsigned long long) mesh_payload[buff_index++] << i*8;
    }

    printf("hop_count=%d; rreq_id=%d; dst_node_id=0x%.16llX; dst_seq_no=%d; src_node_id=0x%.16llX; src_seq_no=%d; prev_hop_id=0x%.16llX\n",
            pkt->hop_count, pkt->rreq_id, pkt->dst_node_id, pkt->dst_seq_no, pkt->src_node_id, pkt->src_seq_no, pkt->prev_hop_id);
}

/**
 *
 * @param mesh_payload      Only mesh packet payload
 * @param size              Size of the mesh packet payload
 * @param pkt               Struct to fill with payload values
 */
void fill_mesh_rrep_struct(uint8_t *mesh_payload, uint16_t size, mesh_rrep_packet_t *pkt)
{
    uint8_t  buff_index = 0;

    pkt->hop_count = mesh_payload[buff_index++];

    // fill the destination nodes id
    for(int i = 0; i < NODE_ID_SIZE; i++) {
        pkt->dst_node_id |= (unsigned long long) mesh_payload[buff_index++] << i*8;
    }
    pkt->dst_seq_no = mesh_payload[buff_index++];

    // fill the source nodes id
    for(int i = 0; i < NODE_ID_SIZE; i++) {
        pkt->src_node_id |= (unsigned long long) mesh_payload[buff_index++] << i*8;
    }

    // fill the previous hop node id
    for(int i = 0; i < NODE_ID_SIZE; i++) {
        pkt->prev_hop_id |= (unsigned long long) mesh_payload[buff_index++] << i*8;
    }

    printf("hop_count=%d; dst_node_id=0x%.16llX; dst_seq_no=%d; src_node_id=0x%.16llX; prev_hop_id=0x%.16llX\n",
           pkt->hop_count, pkt->dst_node_id, pkt->dst_seq_no, pkt->src_node_id, pkt->prev_hop_id);
}

/**
 *
 * @param mesh_payload      Only mesh packet payload
 * @param size              Size of the mesh packet payload
 * @param pkt               Struct to fill with payload values
 */
void fill_mesh_rrer_struct(uint8_t *mesh_payload, uint16_t size, mesh_rrer_packet_t *pkt)
{
    uint8_t  buff_index = 0;

    pkt->dst_count = mesh_payload[buff_index++];

    // fill the destination nodes id
    for(int i = 0; i < NODE_ID_SIZE; i++) {
        pkt->unreachable_node_id |= (unsigned long long) mesh_payload[buff_index++] << i*8;
    }
    pkt->dst_seq_no = mesh_payload[buff_index++];

    printf("dst_count=%d; unreachable_node_id=0x%.16llX; dst_seq_no=%d\n",
           pkt->dst_count, pkt->unreachable_node_id, pkt->dst_seq_no);
}

int update_device_table(uint32_t *device_addr, uint64_t *dst_node_id)
{
    // search if the device_address is already known
    for(int i = 0; i < MAX_DEVICE_TABLE_ENTRIES; i++) {
        if(device_table[i].device_addr == *device_addr) {
            printf("Found the device address into the device table at index %d. Updates the dst_node_id field\n", i);
            device_table[i].dst_node_id = *dst_node_id;
            return 0;
        }
    }

    // search for a free place to add the device_address
    for(int i = 0; i < MAX_DEVICE_TABLE_ENTRIES; i++) {
        if(!device_table[i].valid) {
            printf("Found a free place at index %d", i);
            device_table[i].valid = true;
            device_table[i].dst_node_id = *dst_node_id;
            device_table[i].device_addr = *device_addr;
            return 0;
        }
    }

    // if no more free space in the device table
    printf("ERROR: No more free space in the devices table !!\n");
    return -1;
}

