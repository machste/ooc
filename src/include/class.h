/**
 * @file    class.h
 *
 * @brief   Class
 */
#ifndef _CLASS_H_
#define _CLASS_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Class Definition
 */
typedef struct class class;

struct class {
    const char *name;
    const class *super;
    size_t size;
};

bool issubclass(const void *cls, const void *super);

#ifdef __cplusplus
}
#endif

#endif /* _CLASS_H_ */
