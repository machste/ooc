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
 * @brief Output Interface
 */
typedef struct output {
    // Interfaces have no members.
} output;

/**
 * @brief Output Methods
 */
typedef size_t (*write_cb)(output *self, const char *data, size_t size);
typedef int (*vformat_cb)(output *self, const char *fmt, va_list *va);
typedef bool (*flush_cb)(output *self);

/**
 * @brief Method Table of Output
 */
typedef struct output_mt {
    write_cb write;
    vformat_cb vformat;
    flush_cb flush;
} output_mt;

/**
 * @brief Write to Output
 *
 * @return Number of the written bytes.
 */
size_t write(output *self, const char *data, size_t size);

/**
 * @brief Write Formatted C-String to Output
 *
 * @return  Length of the formatted C-string (excluding the terminating null
 *          byte), if an output error occured, a negativ value is returned.
 */
int format(output *self, const char *fmt, ...);
int vformat(output *self, const char *fmt, va_list *va);

/**
 * @brief Flush Data to an Output
 *
 * Forces a write of all user-space buffered data for the given output or
 * update stream via the stream's underlying write function.
 * 
 * @return True for a successfully flushed output otherwise false
 */
bool flush(output *self);

#ifdef __cplusplus
}
#endif

#endif /* _OUTPUT_IFC_H_ */
