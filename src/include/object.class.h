/**
 * @file    object.class.h
 *
 * @brief   Object Class
 */
#ifndef _OBJECT_CLASS_H_
#define _OBJECT_CLASS_H_

#include <stddef.h>

#include <class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Class Method Definitions
 */
typedef void *(*vinit_cb)(void *self, const void *cls, va_list *va);
typedef void (*destroy_cb)(void *self);
typedef size_t (*to_cstr_cb)(void *self, char *cstr, size_t size);
typedef void (*print_cb)(void *self);

/**
 * @brief Object Class Definition
 */
typedef struct object_class {
    class cls;
    vinit_cb vinit;
    destroy_cb destroy;
    to_cstr_cb to_cstr;
    print_cb print;
} object_class;

/**
 * @brief Initialise an Object
 */
void *init(void *self, const void *cls, ...);

/**
 * @brief Destroy an Object
 *
 * Destroys Objects created by init functions.
 */
void destroy(void *self);

/**
 * @brief Get Class of an Object
 */
const void *class_of(const void *self);

/**
 * @brief Get Name of the Class
 */
const char *name_of(const void *self);

/**
 * @brief Get the Size Needed in the Memory of an Object
 */
size_t size_of(const void *self);

/**
 * @brief Is an Object an Instance Of
 */
bool isinstance(const void *self, const void *cls);

/**
 * @brief Convert to C-String
 *
 * Converts an object to its C-string representation. If 'cstr' is set to NULL
 * or 'size' equals 0 it will return the lenght of the C-string (not including
 * the terminating null byte).
 * 
 * @param cstr  Pointer to a C-string buffer
 * @param len   At most 'size' bytes (including the terminating null byte) are
 *              written to cstr
 * 
 * @return Lenght of the converted C-string
 */
size_t to_cstr(void *self, char *cstr, size_t size);

/**
 * @brief Print to Standard Output
 */
void print(void *self);

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_CLASS_H_ */
