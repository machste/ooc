/**
 * @file    input.class.h
 *
 * @brief   Generic Input Class
 */
#ifndef _INPUT_CLASS_H_
#define _INPUT_CLASS_H_

#include <class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Input Class
 */
extern const class *Input;

/**
 * @brief Input Methods
 */
typedef size_t (*read_cb)(void *self, char *data, size_t size);
typedef int (*vscan_cb)(void *self, const char *fmt, va_list *va);

/**
 * @brief Method Table of Input
 */
typedef struct input_mt {
    read_cb read;
    vscan_cb vscan;
} input_mt;

/**
 * @brief Read from Input
 */
size_t read(void *self, char *data, size_t size);

/**
 * @brief Scan Formatted C-String from Input
 */
int scan(void *self, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* _INPUT_CLASS_H_ */
