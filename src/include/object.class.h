/**
 * @file    object.class.h
 *
 * @brief   Object Class
 */
#ifndef _OBJECT_CLASS_H_
#define _OBJECT_CLASS_H_

#include <stdarg.h>

#include <class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Object Class
 */
extern const class *Object;

/**
 * Forward Declaration of the 'object'
 */
typedef struct object object;

/**
 * Forward Declaration of the 'output' Object
 */
typedef struct output output;

/**
 * Forward Declaration of the 'input' Object
 */
typedef struct input input;

/**
 * @brief Object Methods
 */
typedef void *(*vinit_cb)(object *self, const class *cls, va_list *va);
typedef void (*destroy_cb)(object *self);
typedef int (*put_cb)(object *self, output *out);
typedef int (*take_cb)(object *self, input *in);
typedef size_t (*to_cstr_cb)(object *self, char *cstr, size_t size);

/**
 * @brief Method Table of Object
 */
typedef struct object_mt {
    vinit_cb vinit;
    destroy_cb destroy;
    put_cb put;
    take_cb take;
    to_cstr_cb to_cstr;
} object_mt;

/**
 * @brief Initialise an Object
 */
void *init(object *self, const class *cls, ...);

/**
 * @brief Destroy an Object
 *
 * Destroys Objects created by init functions.
 */
void destroy(object *self);

/**
 * @brief Get Class of an Object
 */
const class *class_of(const object *self);

/**
 * @brief Is an Object an Instance Of
 */
bool isinstance(const object *self, const class *cls);

/**
 * @brief Get Name of the Class
 */
const char *name_of(const object *self);

/**
 * @brief Get the Size Needed in the Memory of an Object
 */
size_t size_of(const object *self);

/**
 * @brief Get Virtual Method Table (VMT) Of a Sub-Class
 *
 * @return Pointer of the VMT of the sub-class, otherwise NULL
 */
const void *mt_of(const object *self, const class *subcls);

/**
 * @brief Put an Object as C-String to an Output
 *
 * This function converts the object 'self' to a displayable string and
 * puts it to an ouput 'out'.
 *
 * @return Lenght of the converted C-string or -1 for error
 */
int put(object *self, output *out);

/**
 * @brief Take an Object as C-String from an Input
 *
 * This function expects a displayable C-string representation of an object,
 * takes it from the input 'in' and converts it to the object 'self'.  
 * 
 * @return Length of the C-string taken from the input or -1 for error
 */
int take(object *self, input *in);

/**
 * @brief Convert to C-String
 *
 * This function converts the object 'self' to its C-string representation.
 * If 'cstr' is set to NULL or 'size' equals 0, it will return the length of
 * the C-string (not including the terminating null byte).
 * 
 * @param cstr  Pointer to a C-string buffer
 * @param len   At most 'size' bytes (including the terminating null byte) that
 *              are going to be written to 'cstr'.
 * 
 * @return Lenght of the converted C-string
 */
size_t to_cstr(object *self, char *cstr, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_CLASS_H_ */
