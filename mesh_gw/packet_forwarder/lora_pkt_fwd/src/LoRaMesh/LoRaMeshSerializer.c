/*
Description: LoRa Mesh protocol message serializer functionality implementation

Maintainer: Joachim Burket
*/


#include "LoRaMesh/LoRaMeshSerializer.h"
#include "utilities.h"

LoRaMeshSerializerStatus_t LoRaMeshSerializerRouteRequest( LoRaMeshMessageRouteRequest_t * meshMsg )
{
    if((meshMsg == 0 ) || (meshMsg->Buffer == 0 ) )
    {
        return LORAMESH_SERIALIZER_ERROR_NPE;
    }

    uint16_t bufItr = 0;

    // Check meshMsg->BufSize
    if(meshMsg->BufSize < LORAMESH_RREQ_MSG_SIZE )
    {
        return LORAMESH_SERIALIZER_ERROR_BUF_SIZE;
    }

    meshMsg->Buffer[bufItr++] = meshMsg->MHDR.Value;

    meshMsg->Buffer[bufItr++] = meshMsg->MeshHDR.Value;

    meshMsg->Buffer[bufItr++] = meshMsg->HopCount;

    meshMsg->Buffer[bufItr++] = meshMsg->RREQ_ID;

    memcpyr(&meshMsg->Buffer[bufItr], meshMsg->DestNodeID, LORAMESH_NODE_ID_FIELD_SIZE );
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->Buffer[bufItr++] = meshMsg->DestSeqNum;

    memcpyr(&meshMsg->Buffer[bufItr], meshMsg->SrcNodeID, LORAMESH_NODE_ID_FIELD_SIZE );
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->Buffer[bufItr++] = meshMsg->SrcSeqNum;

    memcpyr(&meshMsg->Buffer[bufItr], meshMsg->PrevHopNodeID, LORAMESH_NODE_ID_FIELD_SIZE );
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->Buffer[bufItr++] = meshMsg->MIC & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 8 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 16 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 24 ) & 0xFF;

    meshMsg->BufSize = bufItr;

    return LORAMESH_SERIALIZER_SUCCESS;
}

LoRaMeshSerializerStatus_t LoRaMeshSerializerRouteResponse( LoRaMeshMessageRouteResponse_t * meshMsg )
{
    if((meshMsg == 0 ) || (meshMsg->Buffer == 0 ) )
    {
        return LORAMESH_SERIALIZER_ERROR_NPE;
    }

    uint16_t bufItr = 0;

    // Check meshMsg->BufSize
    if(meshMsg->BufSize < LORAMESH_RREQ_MSG_SIZE )
    {
        return LORAMESH_SERIALIZER_ERROR_BUF_SIZE;
    }

    meshMsg->Buffer[bufItr++] = meshMsg->MHDR.Value;

    meshMsg->Buffer[bufItr++] = meshMsg->MeshHDR.Value;

    meshMsg->Buffer[bufItr++] = meshMsg->HopCount;

    memcpyr(&meshMsg->Buffer[bufItr], meshMsg->DestNodeID, LORAMESH_NODE_ID_FIELD_SIZE );
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->Buffer[bufItr++] = meshMsg->DestSeqNum;

    memcpyr(&meshMsg->Buffer[bufItr], meshMsg->SrcNodeID, LORAMESH_NODE_ID_FIELD_SIZE );
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    memcpyr(&meshMsg->Buffer[bufItr], meshMsg->PrevHopNodeID, LORAMESH_NODE_ID_FIELD_SIZE );
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->Buffer[bufItr++] = meshMsg->MIC & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 8 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 16 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 24 ) & 0xFF;

    meshMsg->BufSize = bufItr;

    return LORAMESH_SERIALIZER_SUCCESS;
}

LoRaMeshSerializerStatus_t LoRaMeshSerializerRouteError( LoRaMeshMessageRouteError_t * meshMsg )
{
    if((meshMsg == 0 ) || (meshMsg->Buffer == 0 ) )
    {
        return LORAMESH_SERIALIZER_ERROR_NPE;
    }

    uint16_t bufItr = 0;

    // Check meshMsg->BufSize
    if(meshMsg->BufSize < LORAMESH_RREQ_MSG_SIZE )
    {
        return LORAMESH_SERIALIZER_ERROR_BUF_SIZE;
    }

    meshMsg->Buffer[bufItr++] = meshMsg->MHDR.Value;

    meshMsg->Buffer[bufItr++] = meshMsg->MeshHDR.Value;

    meshMsg->Buffer[bufItr++] = meshMsg->HopCount;

    memcpyr(&meshMsg->Buffer[bufItr], meshMsg->UnreachableDestNodeID, LORAMESH_NODE_ID_FIELD_SIZE );
    bufItr += LORAMESH_NODE_ID_FIELD_SIZE;

    meshMsg->Buffer[bufItr++] = meshMsg->MIC & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 8 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 16 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 24 ) & 0xFF;

    meshMsg->BufSize = bufItr;

    return LORAMESH_SERIALIZER_SUCCESS;
}

LoRaMeshSerializerStatus_t LoRaMeshSerializerData( LoRaMeshMessageData_t* meshMsg )
{
    /**
     * TODO:
     * - Comment calculer si la taille du buffer est suffisamment grande ?
     * - Appeler les méthodes de sérialization selon le type de paquet encapsulé
     */

    if((meshMsg == 0 ) || (meshMsg->Buffer == 0 ) )
    {
        return LORAMESH_SERIALIZER_ERROR_NPE;
    }

    uint16_t bufItr = 0;

#if 0
    /* Check meshMsg->BufSize */
    uint16_t computedBufSize =   LORAMESH_MHDR_FIELD_SIZE
                               + LORAMESH_FHDR_DEV_ADD_FIELD_SIZE
                               + LORAMESH_FHDR_F_CTRL_FIELD_SIZE
                               + LORAMESH_FHDR_F_CNT_FIELD_SIZE;

    computedBufSize += meshMsg->FHDR.FCtrl.Bits.FOptsLen;

    if(meshMsg->FRMPayloadSize > 0 )
    {
        computedBufSize += LORAMESH_F_PORT_FIELD_SIZE;
    }

    computedBufSize += meshMsg->FRMPayloadSize;
    computedBufSize += LORAMESH_MIC_FIELD_SIZE;

    if(meshMsg->BufSize < computedBufSize )
    {
        return LORAMESH_SERIALIZER_ERROR_BUF_SIZE;
    }

    /* Serialize message */
    meshMsg->Buffer[bufItr++] = meshMsg->MHDR.Value;

    meshMsg->Buffer[bufItr++] = ( meshMsg->FHDR.DevAddr ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->FHDR.DevAddr >> 8 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->FHDR.DevAddr >> 16 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->FHDR.DevAddr >> 24 ) & 0xFF;

    meshMsg->Buffer[bufItr++] = meshMsg->FHDR.FCtrl.Value;

    meshMsg->Buffer[bufItr++] = meshMsg->FHDR.FCnt & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->FHDR.FCnt >> 8 ) & 0xFF;

    memcpy1(&meshMsg->Buffer[bufItr], meshMsg->FHDR.FOpts, meshMsg->FHDR.FCtrl.Bits.FOptsLen );
    bufItr = bufItr + meshMsg->FHDR.FCtrl.Bits.FOptsLen;

    if(meshMsg->FRMPayloadSize > 0 )
    {
        meshMsg->Buffer[bufItr++] = meshMsg->FPort;
    }

    memcpy1(&meshMsg->Buffer[bufItr], meshMsg->FRMPayload, meshMsg->FRMPayloadSize );
    bufItr = bufItr + meshMsg->FRMPayloadSize;

    meshMsg->Buffer[bufItr++] = meshMsg->MIC & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 8 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 16 ) & 0xFF;
    meshMsg->Buffer[bufItr++] = ( meshMsg->MIC >> 24 ) & 0xFF;

    meshMsg->BufSize = bufItr;
#endif

    return LORAMESH_SERIALIZER_SUCCESS;
}
