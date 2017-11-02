/**
 * @file    util/octet.h
 *
 * @brief   Octet Module
 *
 * A octet is a representation of 8-bits also known as byte.
 */
#ifndef _UTIL_OCTET_H_
#define _UTIL_OCTET_H_

#include <stddef.h>
#include <stdbool.h>

#include <output.ifc.h>
#include <util/quartet.h>

/**
 * @brief Maximum Value for Octet Type
 */
#define OCTET_MAX 255

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Octet Type
 *
 * The octet type includes integer values from 0 up to 255.
 */
typedef unsigned char octet_t;

/**
 * @brief Hex-Duet Type
 *
 * The hex-duet type consist of two hex-digits.
 */
typedef struct hexduet_t {
    hexdigit_t high;
    hexdigit_t low;
} hexduet_t;

/**
 * @brief Convert a Octet to a Hexadecimal Digit
 */
hexduet_t octet_to_hexduet(octet_t octet);

/**
 * @brief Put an Octet as C-String to an Output
 *
 * This function converts 'octet' to a displayable string and puts it to
 * an output 'out'.
 *
 * @return Lenght of the converted C-string or -1 for error
 */
int octet_put(octet_t octet, output *out);

/**
 * @brief Convert Octet to C-String
 *
 * @param cstr  Pointer to a C-string buffer
 * @param size  At most 'size' bytes (including the terminating null byte) that
 *              are going to be written to 'cstr'.
 *
 * @return Lenght of the converted C-string
 */
size_t octet_to_cstr(octet_t octet, char *cstr, size_t size);

/**
 * @brief Put multiple Octets as C-String to an Output
 *
 * This function converts 'octets' to a displayable string and puts it to
 * an output 'out'.
 *
 * @param octets Pointer to the octet array
 * @param n      Number of octets
 * @param out    Pointer to the output object
 * @param sep    Separator between the hexduets (e.g. ':' -> "00:11:22")
 *
 * @note This method does not match the standard convention of a 'put' method
 *       it acts on multiple octets and thus could be considerd as 's_put'
 *       method.
 *
 * @return Lenght of the converted C-string or -1 for error
 */
int octets_put(octet_t *octets, size_t n, output *out, char sep);

/**
 * @brief Convert Octets to C-String
 *
 * @param octets Pointer to the octet array
 * @param n      Number of octets
 * @param cstr   Pointer to a C-string buffer
 * @param size   At most 'size' bytes (including the terminating null byte) that
 *               are going to be written to 'cstr'.
 * @param sep    Separator between the hexduets (e.g. ':' -> "00:11:22")
 *
 * @note Same note as for the 'octets_put' method, rather think of this method
 *       as 's_to_cstr' method.
 *
 * @return Lenght of the converted C-string
 */
size_t octets_to_cstr(octet_t *octets, size_t n, char *cstr, size_t size,
        char sep);

/**
 * @brief Convert a Hexadecimal Digit to a Octet
 *
 * @param hexduet A hex-duet (e.g. { '1', 'f' } -> 0x1f)
 * @param octet   Pointer to the converted octet.
 *
 * @return True for successful conversion otherwise false
 */
bool hexduet_to_octet(hexduet_t hexduet, octet_t *octet);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_OCTET_H_ */
