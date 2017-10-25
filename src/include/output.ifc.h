/**
 * @file    output.ifc.h
 *
 * @brief   Generic Output Interface
 */
#ifndef _OUTPUT_IFC_H_
#define _OUTPUT_IFC_H_

#include <stdarg.h>

#include <class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Output Interface
 */
extern const class *Output;

/**
 * @brief Output Methods
 */
typedef size_t (*write_cb)(void *self, const char *data, size_t size);
typedef int (*vformat_cb)(void *self, const char *fmt, va_list *va);

/**
 * @brief Method Table of Output
 */
typedef struct output_mt {
    write_cb write;
    vformat_cb vformat;
} output_mt;

/**
 * @brief Output Interface
 */
typedef struct output {
    // Interfaces have no members.
} output;

/**
 * @brief Write to Output
 *
 * @return Number of the written bytes.
 */
size_t write(void *self, const char *data, size_t size);

/**
 * @brief Write Formatted C-String to Output
 *
 * @return  Length of the formatted C-string (excluding the terminating null
 *          byte), if an output error occured, a negativ value is returned.
 */
int format(void *self, const char *fmt, ...);
int vformat(void *self, const char *fmt, va_list *va);

#ifdef __cplusplus
}
#endif

#endif /* _OUTPUT_IFC_H_ */
