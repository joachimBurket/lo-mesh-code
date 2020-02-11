/*!
 * \file      LoRaMeshTypes.h
 *
 * \brief     LoRa Mesh layer internal types definition.
 *
 * \author    Joachim Burket
 *
 */
#ifndef __LORAMESH_TYPES_H__
#define __LORAMESH_TYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>


/*!
 * LoRaMesh Messages types
 *
 */
typedef enum eLoRaMeshMessageType
{
    /*!
     * LoRaMesh Data message
     *
     * Encapsulates a LoRaMac message
     */
    LORAMESH_MSG_TYPE_DATA                       = 0x00,
    /*!
     * LoRaMesh Route Request message
     *
     * Ask a route to a destination
     */
    LORAMESH_MSG_TYPE_ROUTE_REQ                  = 0x01,
    /*!
     * LoRaMesh Route Response message
     *
     * Send the route to a Route Request message
     */
    LORAMESH_MSG_TYPE_ROUTE_RESP                 = 0x02,
    /*!
     * LoRaMesh Route Error message
     *
     * Indicates a broken route
     */
    LORAMESH_MSG_TYPE_ROUTE_ERR                  = 0x03,
    /*!
     * Undefined message type
     */
    LORAMESH_MSG_TYPE_UNDEF                      = 0x04,
}LoRaMeshMessageType_t;

#ifdef __cplusplus
}
#endif

#endif // __LORAMESH_TYPES_H__

