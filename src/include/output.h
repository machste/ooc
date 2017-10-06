/**
 * @file    output.h
 *
 * @brief   Generic Output Object
 */
#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <object.h>
#include <output.class.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const output_class Output;

/**
 * @brief Output Object Definition
 */
struct output {
    object obj;
};

/**
 * @brief Initialise an Output
 *
 * @return Pointer to the initialised 'output' object
 */
output *output_init(output *self);
output *output_vinit(output *self, va_list *va);

/**
 * @brief Destroy an Output
 *
 * This function is used to destroy 'output' objects created by init functions.
 */
void output_destroy(output *self);

/**
 * @brief Write to Output
 */
size_t output_write(output *self, const char *data, size_t size);

/**
 * @brief Write Formatted C-String to Output
 */
int output_format(output *self, const char *fmt, ...);
int output_vformat(output *self, const char *fmt, va_list *va);

/**
 * @brief Standart Output
 */
extern output stdoutput;

#ifdef __cplusplus
}
#endif

#endif /* _OUTPUT_H_ */
