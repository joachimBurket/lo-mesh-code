/*
Description: LoRa Mesh protocol message printer. Prints in the console the different structures.

Maintainer: Joachim Burket
*/
#include "LoRaMesh/LoRaMeshToString.h"
#include "LoRaMac/LoRaMacToString.h"
#include <stdio.h>

static void print_payload(uint8_t *payload, uint8_t size)
{
    for(int i = 0; i < size; i++) {
        printf("%.2X", payload[i]);
    }
    printf("\n");
}

void LoRaMeshRouteRequestToString( LoRaMeshMessageRouteRequest_t *meshMsg )
{
    printf("----- Route Request Mesh Message: -----\n");
    print_payload(meshMsg->Buffer, meshMsg->BufSize);

    printf("MacHeader: RFU=%d, MType=%d\n", meshMsg->MHDR.Bits.RFU, meshMsg->MHDR.Bits.MType);

    printf("MeshHeader: MType=%d\n", meshMsg->MeshHDR.Bits.MType);

    printf("Hop Count: %d\n", meshMsg->HopCount);

    printf("RREQ ID: %d\n", meshMsg->RREQ_ID);

    printf("Destination Node ID:\n");
    print_payload(meshMsg->DestNodeID, LORAMESH_NODE_ID_FIELD_SIZE);
    printf("Destination sequence number: %d\n", meshMsg->DestSeqNum);

    printf("Source Node ID:\n");
    print_payload(meshMsg->SrcNodeID, LORAMESH_NODE_ID_FIELD_SIZE);
    printf("Source sequence number: %d\n", meshMsg->SrcSeqNum);

    printf("Previous Hop Node ID:\n");
    print_payload(meshMsg->PrevHopNodeID, LORAMESH_NODE_ID_FIELD_SIZE);

    printf("MIC = %.8x\n", meshMsg->MIC);
    printf("----- End Of Route Request Message: -----\n");
}

void LoRaMeshRouteResponseToString( LoRaMeshMessageRouteResponse_t *meshMsg )
{
    printf("----- Route Response Mesh Message: -----\n");
    print_payload(meshMsg->Buffer, meshMsg->BufSize);

    printf("MacHeader: RFU=%d, MType=%d\n", meshMsg->MHDR.Bits.RFU, meshMsg->MHDR.Bits.MType);

    printf("MeshHeader: MType=%d\n", meshMsg->MeshHDR.Bits.MType);

    printf("Hop Count: %d\n", meshMsg->HopCount);

    printf("Destination Node ID:\n");
    print_payload(meshMsg->DestNodeID, LORAMESH_NODE_ID_FIELD_SIZE);
    printf("Destination sequence number: %d\n", meshMsg->DestSeqNum);

    printf("Source Node ID:\n");
    print_payload(meshMsg->SrcNodeID, LORAMESH_NODE_ID_FIELD_SIZE);

    printf("Previous Hop Node ID:\n");
    print_payload(meshMsg->PrevHopNodeID, LORAMESH_NODE_ID_FIELD_SIZE);

    printf("MIC = %.8x\n", meshMsg->MIC);
    printf("----- End Of Route Response Message: -----\n");
}

void LoRaMeshRouteErrorToString( LoRaMeshMessageRouteError_t *meshMsg )
{
    printf("----- Route Error Mesh Message: -----\n");
    print_payload(meshMsg->Buffer, meshMsg->BufSize);

    printf("MacHeader: RFU=%d, MType=%d\n", meshMsg->MHDR.Bits.RFU, meshMsg->MHDR.Bits.MType);

    printf("MeshHeader: MType=%d\n", meshMsg->MeshHDR.Bits.MType);

    printf("Hop Count: %d\n", meshMsg->HopCount);

    printf("Destination Node ID:\n");
    print_payload(meshMsg->UnreachableDestNodeID, LORAMESH_NODE_ID_FIELD_SIZE);
    printf("Destination sequence number: %d\n", meshMsg->DestSeqNum);

    printf("MIC = %.8x\n", meshMsg->MIC);
    printf("----- End Of Route Error Message: -----\n");
}

void LoRaMeshDataToString( LoRaMeshMessageData_t *meshMsg )
{
    printf("----- Data Mesh Message: -----\n");
    print_payload(meshMsg->Buffer, meshMsg->BufSize);

    printf("MacHeader: RFU=%d, MType=%d\n", meshMsg->MHDR.Bits.RFU, meshMsg->MHDR.Bits.MType);

    printf("MeshHeader: MType=%d\n", meshMsg->MeshHDR.Bits.MType);

    printf("Destination Node ID:\n");
    print_payload(meshMsg->DestNodeID, LORAMESH_NODE_ID_FIELD_SIZE);

    printf("Source Node ID:\n");
    print_payload(meshMsg->SrcNodeID, LORAMESH_NODE_ID_FIELD_SIZE);

    printf("Device Address: %.8X\n", meshMsg->DevAddr);

    switch(meshMsg->EncapLoRaMacMessage.Type) {
        case LORAMAC_MSG_TYPE_JOIN_REQUEST:
            LoRaMacJoinRequestToString(&meshMsg->EncapLoRaMacMessage.Message.JoinReq);
            break;
        case LORAMAC_MSG_TYPE_JOIN_ACCEPT:
            LoRaMacJoinAcceptToString(&meshMsg->EncapLoRaMacMessage.Message.JoinAccept);
            break;
        case LORAMAC_MSG_TYPE_DATA:
            LoRaMacDataToString(&meshMsg->EncapLoRaMacMessage.Message.Data);
            break;
        default:
            printf("Not printing this LoRaMac message type (%d)\n", meshMsg->EncapLoRaMacMessage.Type);
    }

    printf("MIC = %.8x\n", meshMsg->MIC);
    printf("----- End Of Route Response Message: -----\n");
}