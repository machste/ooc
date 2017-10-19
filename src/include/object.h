/**
 * @file    object.h
 *
 * @brief   Object
 */
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <stdarg.h>

#include <object.class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Object
 */
typedef struct object {
    const class *cls;
} object;

/**
 * Forward Declaration of the 'output' Object
 */
typedef struct output output;

/**
 * Forward Declaration of the 'input' Object
 */
typedef struct input input;

/**
 * @brief Initialise an Object
 *
 * @return Pointer to the initialised 'object'
 */
object *object_init(object *self, const class *cls);
object *object_vinit(object *self, const class *cls, va_list *va);

/**
 * @brief Destroy an Object
 *
 * Destroys objects created by init functions.
 */
void object_destroy(object *self);

/**
 * @brief Put an Object as C-String to an Output
 *
 * This function converts the object 'self' to its C-string representation and
 * puts it to 'out'.  
 * 
 * @return Lenght of the converted C-string or -1 for error
 */
int object_put(object *self, output *out);

/**
 * @brief Take an Object as C-String from an Input
 *
 * This function takes a C-string representation of an object from 'in' and
 * converts it to the object 'self'.  
 * 
 * @return Length of the C-string taken from the input or -1 for error
 */
int object_take(object *self, input *in);

/**
 * @brief Convert to C-String
 *
 * This function converts the object 'self' to its C-string representation.
 * If 'cstr' is set to NULL or 'size' equals 0, it will return the length of
 * the C-string (not including the terminating null byte).
 * 
 * @param cstr  Pointer to a C-string buffer
 * @param len   At most 'size' bytes (including the terminating null byte) are
 *              written to cstr
 * 
 * @return Lenght of the converted C-string
 */
size_t object_to_cstr(object *self, char *cstr, size_t size);

/**
 * @brief Print to Standard Output
 */
void object_print(object *self);

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
