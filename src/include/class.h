/**
 * @file    class.h
 *
 * @brief   Class
 */
#ifndef _CLASS_H_
#define _CLASS_H_

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Class
 */
typedef struct class class;

/**
 * @brief Virtual Method Table
 */
typedef struct vtable vtable;

/**
 * @brief Generic Method Callback
 */
typedef void (*method_cb)(void);

/**
 * @brief Method Table
 */
typedef method_cb * method_table;

/**
 * @brief Class Initialiser Callback
 */
typedef const class *(*class_init_cb)(class *cls);

/**
 * @brief Class Structure
 */
struct class {
    class_init_cb class_init;
    const char *name;
    size_t size;
    size_t vtables_len;
    const vtable *vtables;
};

/**
 * @brief Virtual Method Table Structure
 */
struct vtable {
    const class *cls;
    method_table mt;
};

/**
 * @brief Initialise Class
 */
const class *class_init(class *cls, const char *name, size_t size,
        size_t vtables_len, const vtable *vtables);

/**
 * @brief Is a Class a Sub-Class
 *
 * Is 'subcls' class a sub-class of 'cls'?
 *
 * @return True if conditions is met otherwise False
 */
bool issubclass(const class *cls, const class *subcls);

/**
 * @brief Get Virtual Method Table (VMT) Of a Sub-Class
 *
 * @return Pointer of the VMT of the sub-class, otherwise NULL
 */
const method_table mt_of_class(const class *cls, const class *subcls);

#ifdef __cplusplus
}
#endif

#endif /* _CLASS_H_ */
