/**
 * @file    input.ifc.h
 *
 * @brief   Generic Input Interface
 */
#ifndef _INPUT_IFC_H_
#define _INPUT_IFC_H_

#include <stdarg.h>

#include <class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Input Interface
 */
extern const class *Input;

/**
 * @brief Input Methods
 */
typedef size_t (*read_cb)(void *self, char *data, size_t size);
typedef int (*vscan_cb)(void *self, const char *fmt, va_list *va);
typedef bool (*discard_cb)(void *self);

/**
 * @brief Method Table of Input
 */
typedef struct input_mt {
    read_cb read;
    vscan_cb vscan;
    discard_cb discard;
} input_mt;

/**
 * @brief Input Interface
 */
typedef struct input {
    // Interfaces have no members.
} input;

/**
 * @brief Read from Input
 */
size_t read(void *self, char *data, size_t size);

/**
 * @brief Scan Formatted C-String from Input
 */
int scan(void *self, const char *fmt, ...);
int vscan(void *self, const char *fmt, va_list *va);

/**
 * @brief Discard Data from an Input
 *
 * Discards any buffered data that has been fetched from the underlying file,
 * but has not been consumed by the application.
 * 
 * @return True for a successfully flushed ouput otherwise false
 */
bool discard(void *self);

#ifdef __cplusplus
}
#endif

#endif /* _INPUT_IFC_H_ */
