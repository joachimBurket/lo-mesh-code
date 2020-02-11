/*
Description: LoRa Mac protocol message printer. Prints in the console the different structures.

Maintainer: Joachim Burket
*/
#include "LoRaMac/LoRaMacToString.h"
#include <stdio.h>

static void print_payload(uint8_t *payload, uint8_t size)
{
    for(int i = 0; i < size; i++) {
        printf("%.2X", payload[i]);
    }
    printf("\n");
}

void LoRaMacJoinAcceptToString( LoRaMacMessageJoinAccept_t *macMsg )
{
    printf("----- Join Accept Message: -----\n");
    print_payload(macMsg->Buffer, macMsg->BufSize);

    printf("MacHeader: RFU=%d, MType=%d\n", macMsg->MHDR.Bits.RFU, macMsg->MHDR.Bits.MType);

    printf("Server Nonce:\n");
    print_payload(macMsg->JoinNonce, LORAMAC_JOIN_NONCE_FIELD_SIZE);

    printf("Network ID:\n");
    print_payload(macMsg->NetID, LORAMAC_NET_ID_FIELD_SIZE);

    printf("Device Address: %.8X\n", macMsg->DevAddr);

    // DLSettings, RxDelay, CFList not printed...

    printf("MIC = %.8x\n", macMsg->MIC);
    printf("----- End Of Join Accept Message: -----\n");
}

void LoRaMacJoinRequestToString( LoRaMacMessageJoinRequest_t *macMsg )
{
    printf("----- Join Request Message: -----\n");
    print_payload(macMsg->Buffer, macMsg->BufSize);

    printf("MacHeader: RFU=%d, MType=%d\n", macMsg->MHDR.Bits.RFU, macMsg->MHDR.Bits.MType);

    printf("Join EUI:\n");
    print_payload(macMsg->JoinEUI, LORAMAC_JOIN_EUI_FIELD_SIZE);

    printf("Device ID:\n");
    print_payload(macMsg->DevEUI, LORAMAC_DEV_EUI_FIELD_SIZE);

    printf("Device Nonce: %.2X\n", macMsg->DevNonce);

    printf("MIC = %.8X\n", macMsg->MIC);
    printf("----- End Of Join Request Message: -----\n");
}

void LoRaMacDataToString( LoRaMacMessageData_t *macMsg )
{
    printf("----- Data Message: -----\n");
    print_payload(macMsg->Buffer, macMsg->BufSize);

    printf("MacHeader: RFU=%d, MType=%d\n", macMsg->MHDR.Bits.RFU, macMsg->MHDR.Bits.MType);

    printf("FrameHeader: DevAddr=%.8X, Fcnt=%.2X, FOptsLen=%d, Ack=%d, Adr=%d\n",
            macMsg->FHDR.DevAddr, macMsg->FHDR.FCnt, macMsg->FHDR.FCtrl.Bits.FOptsLen, macMsg->FHDR.FCtrl.Bits.Ack, macMsg->FHDR.FCtrl.Bits.Adr);

    printf("FPort = %d\n", macMsg->FPort);

    if(macMsg->FRMPayloadSize > 0) {
        printf("Frame Payload (size=%d):\n", macMsg->FRMPayloadSize);
        print_payload(macMsg->FRMPayload, macMsg->FRMPayloadSize);
    }

    printf("MIC = %.8x\n", macMsg->MIC);
    printf("----- End Of Data Message: -----\n");
}
