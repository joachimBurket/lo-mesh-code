/*
Description: LoRa Mesh protocol message parser functionality implementation

Maintainer: Joachim Burket
*/

#include "LoRaMesh/LoRaMeshParser.h"
#include "LoRaMac/LoRaMacParser.h"
#include "LoRaMac/LoRaMacTypes.h"
#include "utilities.h"
#include <stdio.h>

LoRaMeshParserStatus_t LoRaMeshParserRouteRequest( LoRaMeshMessageRouteRequest_t * meshMsg )
{
    if((meshMsg == 0 ) || (meshMsg->Buffer == 0 ) ) {
        return LORAMESH_PARSER_ERROR_NPE;
    }

    uint16_t bufItr = 0;

    meshMsg->MHDR.Value = meshMsg->Buffer[bufItr++];

    meshMsg->MeshHDR.Value = meshMsg->Buffer[bufItr++];

    meshMsg->HopCount = meshMsg->Buffer[bufItr++];

    meshMsg->RREQ_ID = meshMsg->Buffer[bufItr++];

    memcpy1(meshMsg->DestNodeID, &meshMsg->Buffer[bufItr], LORAMESH_NODE_ID_FIELD_SIZE);
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->DestSeqNum = meshMsg->Buffer[bufItr++];

    memcpy1(meshMsg->SrcNodeID, &meshMsg->Buffer[bufItr], LORAMESH_NODE_ID_FIELD_SIZE);
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->SrcSeqNum = meshMsg->Buffer[bufItr++];

    memcpy1(meshMsg->PrevHopNodeID, &meshMsg->Buffer[bufItr], LORAMESH_NODE_ID_FIELD_SIZE);
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    if((meshMsg->BufSize - LORAMAC_MIC_FIELD_SIZE - bufItr ) > 0 ) {
        return LORAMESH_PARSER_FAIL;
    }

    meshMsg->MIC = ( uint32_t ) meshMsg->Buffer[bufItr++];
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 8 );
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 16 );
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 24 );

    return LORAMESH_PARSER_SUCCESS;
}

LoRaMeshParserStatus_t LoRaMeshParserRouteResponse( LoRaMeshMessageRouteResponse_t * meshMsg )
{
    if((meshMsg == 0 ) || (meshMsg->Buffer == 0 ) ) {
        return LORAMESH_PARSER_ERROR_NPE;
    }

    uint16_t bufItr = 0;

    meshMsg->MHDR.Value = meshMsg->Buffer[bufItr++];

    meshMsg->MeshHDR.Value = meshMsg->Buffer[bufItr++];

    meshMsg->HopCount = meshMsg->Buffer[bufItr++];

    memcpy1(meshMsg->DestNodeID, &meshMsg->Buffer[bufItr], LORAMESH_NODE_ID_FIELD_SIZE);
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->DestSeqNum = meshMsg->Buffer[bufItr++];

    memcpy1(meshMsg->SrcNodeID, &meshMsg->Buffer[bufItr], LORAMESH_NODE_ID_FIELD_SIZE);
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    memcpy1(meshMsg->PrevHopNodeID, &meshMsg->Buffer[bufItr], LORAMESH_NODE_ID_FIELD_SIZE);
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    if((meshMsg->BufSize - LORAMAC_MIC_FIELD_SIZE - bufItr ) > 0 ) {
        return LORAMESH_PARSER_FAIL;
    }

    meshMsg->MIC = ( uint32_t ) meshMsg->Buffer[bufItr++];
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 8 );
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 16 );
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 24 );

    return LORAMESH_PARSER_SUCCESS;
}

LoRaMeshParserStatus_t LoRaMeshParserRouteError( LoRaMeshMessageRouteError_t * meshMsg )
{
    if((meshMsg == 0 ) || (meshMsg->Buffer == 0 ) ) {
        return LORAMESH_PARSER_ERROR_NPE;
    }

    uint16_t bufItr = 0;

    meshMsg->MHDR.Value = meshMsg->Buffer[bufItr++];

    meshMsg->MeshHDR.Value = meshMsg->Buffer[bufItr++];

    meshMsg->HopCount = meshMsg->Buffer[bufItr++];


    memcpy1(meshMsg->UnreachableDestNodeID, &meshMsg->Buffer[bufItr], LORAMESH_NODE_ID_FIELD_SIZE);
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->DestSeqNum = meshMsg->Buffer[bufItr++];

    if((meshMsg->BufSize - LORAMAC_MIC_FIELD_SIZE - bufItr ) > 0 ) {
        return LORAMESH_PARSER_FAIL;
    }

    meshMsg->MIC = ( uint32_t ) meshMsg->Buffer[bufItr++];
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 8 );
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 16 );
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 24 );

    return LORAMESH_PARSER_SUCCESS;
}

LoRaMeshParserStatus_t LoRaMeshParserData( LoRaMeshMessageData_t * meshMsg )
{
    if((meshMsg == 0 ) || (meshMsg->Buffer == 0 ) ) {
        return LORAMESH_PARSER_ERROR_NPE;
    }

    uint16_t bufItr = 0;

    meshMsg->MHDR.Value = meshMsg->Buffer[bufItr++];

    meshMsg->MeshHDR.Value = meshMsg->Buffer[bufItr++];

    memcpy1(meshMsg->DestNodeID, &meshMsg->Buffer[bufItr], LORAMESH_NODE_ID_FIELD_SIZE);
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    memcpy1(meshMsg->SrcNodeID, &meshMsg->Buffer[bufItr], LORAMESH_NODE_ID_FIELD_SIZE);
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->DevAddr = ( uint32_t ) meshMsg->Buffer[bufItr++];
    meshMsg->DevAddr |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 8 );
    meshMsg->DevAddr |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 16 );
    meshMsg->DevAddr |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 24 );

    if(( meshMsg->BufSize - LORAMAC_MIC_FIELD_SIZE - bufItr ) > 0 ) {
        // Parse LoRaMac encapsulated message
        LoRaMacHeader_t macHdr;

        macHdr.Value = meshMsg->Buffer[bufItr];

        switch (macHdr.Bits.MType) {
            case FRAME_TYPE_JOIN_ACCEPT:
                meshMsg->EncapLoRaMacMessage.Type = LORAMAC_MSG_TYPE_JOIN_ACCEPT;
                meshMsg->EncapLoRaMacMessage.Message.JoinAccept.Buffer = &meshMsg->Buffer[bufItr];
                meshMsg->EncapLoRaMacMessage.Message.JoinAccept.BufSize = ( meshMsg->BufSize - LORAMAC_MIC_FIELD_SIZE - bufItr );

                if( LORAMAC_PARSER_SUCCESS != LoRaMacParserJoinAccept( &meshMsg->EncapLoRaMacMessage.Message.JoinAccept ) ) {
                    printf("LoRaMacParserJoinAccept error on encapsulated LoRaMac message\n");
                    return LORAMESH_PARSER_ERROR;
                }
                break;
            case FRAME_TYPE_JOIN_REQ:
                // TODO
            case FRAME_TYPE_DATA_CONFIRMED_DOWN:
            case FRAME_TYPE_DATA_CONFIRMED_UP:
            case FRAME_TYPE_DATA_UNCONFIRMED_DOWN:
            case FRAME_TYPE_DATA_UNCONFIRMED_UP:
                // TODO: Parser?
            default:
                printf("Unknown encapsulated LoRaMac message");
        }
    }

    meshMsg->MIC = ( uint32_t ) meshMsg->Buffer[bufItr++];
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 8 );
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 16 );
    meshMsg->MIC |= ( ( uint32_t ) meshMsg->Buffer[bufItr++] << 24 );

    return LORAMESH_PARSER_SUCCESS;
}