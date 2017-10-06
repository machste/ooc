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
 * @brief Class Definition
 */
typedef struct class class;

struct class {
    const class *(*class_init)(void);
    const char *name;
    size_t size;
    const void *mt;
    const class *super;
    const void **vmts;
};

/**
 * @brief Initialise Class
 */
const class *class_init(const class *cls, const char *name, size_t size,
        const void *mt, const class *super, const void **vmts);

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
const void *mt_of_class(const class *cls, const class *subcls);

#ifdef __cplusplus
}
#endif

#endif /* _CLASS_H_ */
