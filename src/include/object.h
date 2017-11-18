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
 * @brief Initialise an Object
 *
 * Object specific implementation of init().
 */
object *object_init(object *self, const class *cls);
object *object_vinit(object *self, const class *cls, va_list *va);

/**
 * Object specific implementation of destroy()
 */
void object_destroy(object *self);

/**
 * Object specific implementation of put()
 */
int object_put(object *self, output *out);

/**
 * Object specific implementation of take()
 */
int object_take(object *self, input *in);

/**
 * Object specific implementation of to_cstr()
 */
size_t object_to_cstr(object *self, char *cstr, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
