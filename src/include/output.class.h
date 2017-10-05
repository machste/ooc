/**
 * @file    output.class.h
 *
 * @brief   Generic Output Class
 */
#ifndef _OUTPUT_CLASS_H_
#define _OUTPUT_CLASS_H_

#include <object.class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Class Method Definitions
 */
typedef size_t (*write_cb)(void *self, const char *data, size_t size);
typedef int (*vformat_cb)(void *self, const char *fmt, va_list *va);

/**
 * @brief Generic Output Class Definition
 */
typedef struct output_class {
    object_class object_cls;
    write_cb write;
    vformat_cb vformat;
} output_class;

#ifdef __cplusplus
}
#endif

/**
 * @brief Write to Output
 */
size_t write(void *self, const char *data, size_t size);

/**
 * @brief Write Formatted C-String to Output
 */
int format(void *self, const char *fmt, ...);


#endif /* _OUTPUT_CLASS_H_ */
