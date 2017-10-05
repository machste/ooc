/**
 * @file    input.h
 *
 * @brief   Generic Input Object
 */
#ifndef _INPUT_H_
#define _INPUT_H_

#include <object.h>
#include <input.class.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const input_class Input;

/**
 * @brief Input Object Definition
 */
struct input {
    object obj;
};

/**
 * @brief Initialise an Input
 *
 * @return Pointer to the initialised 'input' object
 */
input *input_init(input *self);
input *input_vinit(input *self, va_list *va);

/**
 * @brief Destroy an Input
 *
 * This function is used to destroy 'input' objects created by init functions.
 */
void input_destroy(input *self);

/**
 * @brief Read from Input
 */
size_t input_read(input *self, char *data, size_t size);

/**
 * @brief Scan Formatted C-String from Input
 */
int input_scan(input *self, const char *fmt, ...);
int input_vscan(input *self, const char *fmt, va_list *va);

/**
 * @brief Standart Input
 */
extern input stdinput;

#ifdef __cplusplus
}
#endif

#endif /* _INPUT_H_ */
