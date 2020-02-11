/*!
 * \file      LoRaMeshParser.h
 *
 * \brief     LoRa Mesh protocol message parser functionality implementation
 *
 * \author    Joachim Burket
 *
 */
#ifndef __LORAMESH_PARSER_H__
#define __LORAMESH_PARSER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "LoRaMeshMessageTypes.h"

/*!
 * LoRaMesh Parser Status
 */
typedef enum eLoRaMeshParserStatus
{
    /*!
     * No error occurred
     */
    LORAMESH_PARSER_SUCCESS = 0,
    /*!
     * Failure during parsing occurred
     */
    LORAMESH_PARSER_FAIL,
    /*!
     * Null pointer exception
     */
    LORAMESH_PARSER_ERROR_NPE,
    /*!
     * Undefined Error occurred
     */
    LORAMESH_PARSER_ERROR,
}LoRaMeshParserStatus_t;


/*!
 * Parse a serialized Route Request message and fills the structured object.
 *
 * \param[IN/OUT] meshMsg      - Route Request message object
 * \retval                     - Status of the operation
 */
LoRaMeshParserStatus_t LoRaMeshParserRouteRequest( LoRaMeshMessageRouteRequest_t *meshMsg );

/*!
 * Parse a serialized Route Response message and fills the structured object.
 *
 * \param[IN/OUT] meshMsg      - Route Response message object
 * \retval                     - Status of the operation
 */
LoRaMeshParserStatus_t LoRaMeshParserRouteResponse( LoRaMeshMessageRouteResponse_t *meshMsg );

/*!
 * Parse a serialized Route Error message and fills the structured object.
 *
 * \param[IN/OUT] meshMsg      - Route Error message object
 * \retval                     - Status of the operation
 */
LoRaMeshParserStatus_t LoRaMeshParserRouteError( LoRaMeshMessageRouteError_t *meshMsg );

/*!
 * Parse a serialized Data message and fills the structured object.
 *
 * \param[IN/OUT] meshMsg      - Data message object
 * \retval                     - Status of the operation
 */
LoRaMeshParserStatus_t LoRaMeshParserData( LoRaMeshMessageData_t *meshMsg );

#ifdef __cplusplus
}
#endif

#endif // __LORAMESH_PARSER_H__

