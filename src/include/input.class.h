/**
 * @file    input.class.h
 *
 * @brief   Generic Input Class
 */
#ifndef _INPUT_CLASS_H_
#define _INPUT_CLASS_H_

#include <object.class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Class Method Definitions
 */
typedef size_t (*read_cb)(void *self, char *data, size_t size);
typedef int (*vscan_cb)(void *self, const char *fmt, va_list *va);

/**
 * @brief Generic Input Class Definition
 */
typedef struct input_class {
    object_class object_cls;
    read_cb read;
    vscan_cb vscan;
} input_class;

#ifdef __cplusplus
}
#endif

/**
 * @brief Read from Input
 */
size_t read(void *self, char *data, size_t size);

/**
 * @brief Scan Formatted C-String from Input
 */
int scan(void *self, const char *fmt, ...);


#endif /* _INPUT_CLASS_H_ */
