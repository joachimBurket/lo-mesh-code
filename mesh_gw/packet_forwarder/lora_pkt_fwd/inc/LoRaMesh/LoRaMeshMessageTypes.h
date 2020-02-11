/*!
 * \file      LoRaMeshMessageTypes.h
 *
 * \brief     LoRa Mesh protocol messages type definitions
 *
 * \author    Joachim Burket
 *
 */
#ifndef __LORAMESH_MESSAGE_TYPES_H__
#define __LORAMESH_MESSAGE_TYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "LoRaMesh/LoRaMeshTypes.h"
#include "LoRaMesh/LoRaMeshHeaderTypes.h"
#include "LoRaMac/LoRaMacHeaderTypes.h"
#include "LoRaMac/LoRaMacMessageTypes.h"

/*! Mesh header field size */
#define LORAMESH_MHDR_FIELD_SIZE            1

/*! Hop count field size */
#define LORAMESH_HOP_COUNT_FIELD_SIZE       1

/*! RREQ_ID field size */
#define LORAMESH_RREQ_ID_FIELD_SIZE         1

/*! Node ID field size */
#define LORAMESH_NODE_ID_FIELD_SIZE         6

/*! Sequence number field size */
#define LORAMESH_SEQ_NUM_FIELD_SIZE         1

/*! Device address field size */
#define LORAMESH_DEV_ADDR_FIELD_SIZE        4

/*! Route Request message size:
 * MHDR (1) + MeshHDR (1) + RREQ_SIZE (22) + MIC (4) */
#define LORAMESH_RREQ_MSG_SIZE              28

/*! Route Response message size:
 * MHDR (1) + MeshHDR (1) + RREP_SIZE (20) + MIC (4) */
#define LORAMESH_RREP_MSG_SIZE              26

/*! Route Error message size:
 * MHDR (1) + MeshHDR (1) + RRER_SIZE (8) + MIC (4) */
#define LORAMESH_RRER_MSG_SIZE              14


/*!
 * LoRaMesh type for Data Mesh messages
 */
typedef struct sLoRaMeshMessageData
{
    /*!
     * Serialized message buffer
     */
    uint8_t* Buffer;
    /*!
     * Size of serialized message buffer
     */
    uint8_t BufSize;
    /*!
     * MAC header
     */
    LoRaMacHeader_t MHDR;
    /*!
     * Mesh header
     */
    LoRaMeshHeader_t MeshHDR;
    /*!
     * Destination Node ID
     */
    uint8_t DestNodeID[LORAMESH_NODE_ID_FIELD_SIZE];
    /*!
     * Source Node ID
     */
    uint8_t SrcNodeID[LORAMESH_NODE_ID_FIELD_SIZE];
    /*!
     * Device Address
     */
    uint32_t DevAddr;
    /*!
     * Encapsulated LoRaMac message
     */
    LoRaMacMessage_t EncapLoRaMacMessage;
    /*!
     * Message integrity code (MIC)
     */
    uint32_t MIC;
}LoRaMeshMessageData_t;

/*!
 * LoRaMesh type for RouteRequest message (RREQ)
 */
typedef struct sLoRaMeshMessageRouteRequest
{
    /*!
     * Serialized message buffer
     */
    uint8_t* Buffer;
    /*!
     * Size of serialized message buffer
     */
    uint8_t BufSize;
    /*!
     * MAC header
     */
    LoRaMacHeader_t MHDR;
    /*!
     * Mesh header
     */
    LoRaMeshHeader_t MeshHDR;
    /*!
     *  Hop Count
     */
    uint8_t HopCount;
    /*!
     * RREQ ID
     */
    uint8_t RREQ_ID;
    /*!
     * Destination Node ID
     */
    uint8_t DestNodeID[LORAMESH_NODE_ID_FIELD_SIZE];
    /*!
     *  Destination Sequence Number
     */
    uint8_t DestSeqNum;
    /*!
     * Source Node ID
     */
    uint8_t SrcNodeID[LORAMESH_NODE_ID_FIELD_SIZE];
    /*!
     *  Source Sequence Number
     */
    uint8_t SrcSeqNum;
    /*!
     * Previous Hop Node ID
     */
    uint8_t PrevHopNodeID[LORAMESH_NODE_ID_FIELD_SIZE];
    /*!
     * Message integrity code (MIC)
     */
    uint32_t MIC;
}LoRaMeshMessageRouteRequest_t;

/*!
 * LoRaMesh type for RouteResponse message (RREP)
 */
typedef struct sLoRaMeshMessageRouteResponse
{
    /*!
     * Serialized message buffer
     */
    uint8_t* Buffer;
    /*!
     * Size of serialized message buffer
     */
    uint8_t BufSize;
    /*!
     * MAC header
     */
    LoRaMacHeader_t MHDR;
    /*!
     * Mesh header
     */
    LoRaMeshHeader_t MeshHDR;
    /*!
     *  Hop Count
     */
    uint8_t HopCount;
    /*!
     * Destination Node ID
     */
    uint8_t DestNodeID[LORAMESH_NODE_ID_FIELD_SIZE];
    /*!
     *  Destination Sequence Number
     */
    uint8_t DestSeqNum;
    /*!
     * Source Node ID
     */
    uint8_t SrcNodeID[LORAMESH_NODE_ID_FIELD_SIZE];
    /*!
     * Previous Hop Node ID
     */
    uint8_t PrevHopNodeID[LORAMESH_NODE_ID_FIELD_SIZE];
    /*!
     * Message integrity code (MIC)
     */
    uint32_t MIC;
}LoRaMeshMessageRouteResponse_t;

/*!
 * LoRaMesh type for RouteError message (RRER)
 */
typedef struct sLoRaMeshMessageRouteError
{
    /*!
     * Serialized message buffer
     */
    uint8_t* Buffer;
    /*!
     * Size of serialized message buffer
     */
    uint8_t BufSize;
    /*!
     * MAC header
     */
    LoRaMacHeader_t MHDR;
    /*!
     * Mesh header
     */
    LoRaMeshHeader_t MeshHDR;
    /*!
     *  Hop Count
     */
    uint8_t HopCount;
    /*!
     * Unreachable Destination Node ID
     */
    uint8_t UnreachableDestNodeID[LORAMESH_NODE_ID_FIELD_SIZE];
    /*!
     *  Destination Sequence Number
     */
    uint8_t DestSeqNum;
    /*!
     * Message integrity code (MIC)
     */
    uint32_t MIC;
}LoRaMeshMessageRouteError_t;

/*!
 * LoRaMesh general message type
 */
typedef struct sLoRaMeshMessage
{
    LoRaMeshMessageType_t Type;
    union uMeshMessage
    {
        LoRaMeshMessageRouteRequest_t RouteReq;
        LoRaMeshMessageRouteRequest_t RouteRep;
        LoRaMeshMessageRouteRequest_t RouteErr;
        LoRaMeshMessageData_t Data;
    }Message;
}LoRaMeshMessage_t;

#ifdef __cplusplus
}
#endif

#endif // __LORAMESH_MESSAGE_TYPES_H__
