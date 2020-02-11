/*!
 * \file      LoRaMeshHeaderTypes.h
 *
 * \brief     LoRa Mesh protocol header type definitions
 *
 * \author    Joachim Burket
 *
 */
#ifndef __LORAMESH_HEADER_TYPES_H__
#define __LORAMESH_HEADER_TYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>


/*!
 * LoRaMesh header field definition (MeshHDR field)
 *
 */
typedef union uLoRaMeshHeader
{
    /*!
     * Byte-access to the bits
     */
    uint8_t Value;
    /*!
     * Structure containing single access to header bits
     */
    struct sMeshHeaderBits
    {
        /*!
         * Reserved bits
         */
        uint8_t Reserved        : 5;
        /*!
         * Message type
         */
        uint8_t MType           : 3;
    }Bits;
}LoRaMeshHeader_t;


#ifdef __cplusplus
}
#endif

#endif // __LORAMESH_HEADER_TYPES_H__
