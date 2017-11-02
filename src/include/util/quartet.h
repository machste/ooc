/**
 * @file    util/quartet.h
 *
 * @brief   Quartet Module
 *
 * A quartet is a representation of 4-bits also known as nibble, similar to the
 * octet which is a representation of 8-bits which equals a byte.
 */
#ifndef _UTIL_QUARTET_H_
#define _UTIL_QUARTET_H_

#include <stdbool.h>

/**
 * @brief Maximum Value for Quartet Type
 */
#define QUARTET_MAX 15

/**
 * @brief Get the Low Quartet of a Byte
 */
#define QUARTET_LO(byte) ((byte) & 0x0F)

/**
 * @brief Get the High Quartet of a Byte
 */
#define QUARTET_HI(byte) (((byte) >> 4) & 0x0F)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Quartet Type
 *
 * The quartet type includes integer values from 0 up to 15.
 */
typedef unsigned char quartet_t;

/**
 * @brief Hex-Digit Type
 *
 * The hex-digit type includes characters from '0' up to 'f'.
 */
typedef char hexdigit_t;

/**
 * @brief Check if Quartet is Valid
 *
 * @return True for a valid quartet otherwise false
 */
bool quartet_valid(quartet_t quartet);

/**
 * @brief Convert a Quartet to a Hexadecimal Digit
 */
hexdigit_t quartet_hexdigit(quartet_t quartet);

/**
 * @brief Convert a Hexadecimal Digit to a Quartet
 */
quartet_t hexdigit_to_quartet(hexdigit_t hexdigit);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_QUARTET_H_ */
