/*!
 * \file      LoRaMacToString.h
 *
 * \brief     LoRa Mac protocol message printer. Prints in the console the parsed structures.
 *
 * \author    Joachim Burket
 *
 */
#ifndef __LORAMAC_TO_STRING_H__
#define __LORAMAC_TO_STRING_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "LoRaMac/LoRaMacMessageTypes.h"


/*!
 * Prints a JoinAccept structure in the console
 *
 * \param[IN/OUT] macMsg       - Join-accept message object. Must have been parsed before
 */
void LoRaMacJoinAcceptToString( LoRaMacMessageJoinAccept_t *macMsg );

/*!
 * Prints a JoinRequest structure in the console
 *
 * \param[IN/OUT] macMsg       - Join-request message object. Must have been parsed before
 */
void LoRaMacJoinRequestToString( LoRaMacMessageJoinRequest_t *macMsg );

/*!
 * Prints a Data structure in the console
 *
 * \param[IN/OUT] macMsg       - Data message object. Must have been parsed before
 */
void LoRaMacDataToString( LoRaMacMessageData_t *macMsg );

/*! \} addtogroup LORAMAC */

#ifdef __cplusplus
}
#endif

#endif // __LORAMAC_TO_STRING_H__

