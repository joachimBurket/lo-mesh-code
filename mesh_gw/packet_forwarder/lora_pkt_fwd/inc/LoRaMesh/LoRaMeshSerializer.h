/*!
 * \file      LoRaMeshHeaderTypes.h
 *
 * \brief     LoRa Mesh protocol message serializer functionality implementation
 *
 * \author    Joachim Burket
 *
 */
#ifndef __LORAMESH_SERIALIZER_H__
#define __LORAMESH_SERIALIZER_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include "LoRaMesh/LoRaMeshMessageTypes.h"


/*!
 * LoRaMesh Serializer Status
 */
typedef enum eLoRaMeshSerializerStatus
{
    /*!
     * No error occurred
     */
    LORAMESH_SERIALIZER_SUCCESS = 0,
    /*!
     * Null pointer exception
     */
    LORAMESH_SERIALIZER_ERROR_NPE,
    /*!
     * Incompatible buffer size
     */
    LORAMESH_SERIALIZER_ERROR_BUF_SIZE,
    /*!
     * Undefined Error occurred
     */
    LORAMESH_SERIALIZER_ERROR,
}LoRaMeshSerializerStatus_t;

/*!
 * Creates serialized Mesh message of structured object.
 *
 * \param[IN/OUT] macMsg        - Route Request message object
 * \retval                      - Status of the operation
 */
LoRaMeshSerializerStatus_t LoRaMeshSerializerRouteRequest( LoRaMeshMessageRouteRequest_t* meshMsg );

/*!
 * Creates serialized Mesh message of structured object.
 *
 * \param[IN/OUT] macMsg        - Route Response message object
 * \retval                      - Status of the operation
 */
LoRaMeshSerializerStatus_t LoRaMeshSerializerRouteResponse( LoRaMeshMessageRouteResponse_t * meshMsg );

/*!
 * Creates serialized Mesh message of structured object.
 *
 * \param[IN/OUT] macMsg        - Route Error message object
 * \retval                      - Status of the operation
 */
LoRaMeshSerializerStatus_t LoRaMeshSerializerRouteError( LoRaMeshMessageRouteError_t * meshMsg );

/*!
 * Creates serialized MAC message of structured object.
 *
 * \param[IN/OUT] meshMsg        - Data message object
 * \retval                      - Status of the operation
 */
LoRaMeshSerializerStatus_t LoRaMeshSerializerData( LoRaMeshMessageData_t* meshMsg );

#ifdef __cplusplus
}
#endif

#endif // __LORAMESH_SERIALIZER_H__

