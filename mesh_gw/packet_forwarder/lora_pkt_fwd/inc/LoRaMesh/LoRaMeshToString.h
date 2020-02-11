/*!
 * \file      LoRaMeshToString.h
 *
 * \brief     LoRa Mesh protocol message printer
 *
 * \author    Joachim Burket
 *
 */
#ifndef __LORAMESH_TO_STRING_H__
#define __LORAMESH_TO_STRING_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "LoRaMeshMessageTypes.h"

/*!
* Prints a RouteRequest structure in the console
*
* \param[IN/OUT] meshMsg       - RouteRequest message object. Must have been parsed before
*/
void LoRaMeshRouteRequestToString( LoRaMeshMessageRouteRequest_t *meshMsg );

/*!
* Prints a RouteResponse structure in the console
*
* \param[IN/OUT] meshMsg       - RouteResponse message object. Must have been parsed before
*/
void LoRaMeshRouteResponseToString( LoRaMeshMessageRouteResponse_t *meshMsg );

/*!
* Prints a RouteError structure in the console
*
* \param[IN/OUT] meshMsg       - RouteError message object. Must have been parsed before
*/
void LoRaMeshRouteErrorToString( LoRaMeshMessageRouteError_t *meshMsg );

/*!
* Prints a Data structure in the console
*
* \param[IN/OUT] meshMsg       - Data message object. Must have been parsed before
*/
void LoRaMeshDataToString( LoRaMeshMessageData_t *meshMsg );

#ifdef __cplusplus
}
#endif

#endif // __LORAMESH_TO_STRING_H__

