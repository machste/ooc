/**
 * @file    util/sbuffer.h
 *
 * @brief   Static Buffer Object
 */
#ifndef _UTIL_SBUFFER_H_
#define _UTIL_SBUFFER_H_

#include <object.h>
#include <input.ifc.h>
#include <output.ifc.h>
#include <container.ifc.h>
#include <util/sbuffer.class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Static Buffer Object
 */
typedef struct sbuffer {
    union {
        object;
        container;
        output;
        input;
    };
    size_t size;
    char *data;
} sbuffer;

/**
 *@brief Static Buffer specific implementation of init()
 */
sbuffer *sbuffer_init(sbuffer *self, const class *cls, char *data, size_t size);
sbuffer *sbuffer_vinit(sbuffer *self, const class *cls, va_list *va);

/**
 * @brief Static Buffer specific implementation of put()
 */
int sbuffer_put(sbuffer *self, output *out);

/**
 * @brief Static Buffer specific implementation of len()
 */
size_t sbuffer_len(sbuffer *self);

/**
 * @brief Static Buffer specific implementation of get_at()
 */
char *sbuffer_get_at(sbuffer *self, int index);

/**
 * @brief Static Buffer specific implementation of set_at()
 */
char *sbuffer_set_at(sbuffer *self, int index, char *item);

/**
 * @brief Static Buffer specific implementation of clear()
 */
void sbuffer_clear(sbuffer *self);

/**
 * @brief Static Buffer specific implementation of read()
 */
size_t sbuffer_read(sbuffer *self, char *data, size_t size);

/**
 * @brief Static Buffer specific implementation of write()
 */
size_t sbuffer_write(sbuffer *self, const char *data, size_t size);

/**
 * @brief Static Buffer specific implementation of scan()
 */
int sbuffer_scan(sbuffer *self, const char *fmt, ...);
int sbuffer_vscan(sbuffer *self, const char *fmt, va_list *va);

/**
 * @brief Static Buffer specific implementation of format()
 */
int sbuffer_format(sbuffer *self, const char *fmt, ...);
int sbuffer_vformat(sbuffer *self, const char *fmt, va_list *va);

/**
 * @brief Static Buffer specific implementation of 'discard()'
 */
bool sbuffer_discard(sbuffer *self);

/**
 * @brief Static Buffer specific implementation of 'flush()'
 */
bool sbuffer_flush(sbuffer *self);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_SBUFFER_H_ */
