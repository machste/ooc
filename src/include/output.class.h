/**
 * @file    output.class.h
 *
 * @brief   Generic Output Class
 */
#ifndef _OUTPUT_CLASS_H_
#define _OUTPUT_CLASS_H_

#include <output.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Output Class
 */
extern const class Output;

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
 * @brief Write to Output
 */
size_t write(void *self, const char *data, size_t size);

/**
 * @brief Write Formatted C-String to Output
 */
int format(void *self, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* _OUTPUT_CLASS_H_ */
