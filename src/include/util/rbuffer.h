/**
 * @file    util/rbuffer.h
 *
 * @brief   Ring Buffer Object
 */
#ifndef _UTIL_RBUFFER_H_
#define _UTIL_RBUFFER_H_

#include <input.ifc.h>
#include <output.ifc.h>
#include <util/sbuffer.h>
#include <util/rbuffer.class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Ring Buffer Object
 */
typedef struct rbuffer {
    sbuffer sbuf;
    size_t head;
    size_t foot;
} rbuffer;

/**
 * @brief Ring Buffer specific implementation of init()
 */
rbuffer *rbuffer_init(rbuffer *self, const class *cls, char *data, size_t size);
rbuffer *rbuffer_vinit(rbuffer *self, const class *cls, va_list *va);

/**
 * @brief Ring Buffer specific implementation of len()
 *
 * @note The size of the ring buffer is one byte smaller than 'size', that is
 * because of one byte is spared as guard between the 'head' and 'foot'
 * pointer.
 */
size_t rbuffer_len(rbuffer *self);

/**
 * @brief Ring Buffer specific implementation of get_at()
 *
 * @note Index 0 is at the location of the 'foot' pointer of the ring buffer.
 */
char *rbuffer_get_at(rbuffer *self, int index);

/**
 * @brief Ring Buffer specific implementation of clear()
 */
void rbuffer_clear(rbuffer *self);

/**
 * @brief Ring Buffer specific implementation of read()
 */
size_t rbuffer_read(rbuffer *self, char *data, size_t size);

/**
 * @brief Fill Empty Part of the Ring Buffer
 *
 * Fill the empty part of the ring buffer 'self' with the given character 'c'.
 */
void rbuffer_fill_empty(rbuffer *self, char c);

/**
 * @brief Ring Buffer specific implementation of write()
 */
size_t rbuffer_write(rbuffer *self, const char *data, size_t size);

/**
 * @brief Ring Buffer specific implementation of scan()
 */
int rbuffer_scan(rbuffer *self, const char *fmt, ...);
int rbuffer_vscan(rbuffer *self, const char *fmt, va_list *va);

/**
 * @brief Ring Buffer specific implementation of format()
 */
int rbuffer_format(rbuffer *self, const char *fmt, ...);
int rbuffer_vformat(rbuffer *self, const char *fmt, va_list *va);

/**
 * @brief Ring Buffer specific implementation of 'discard()'
 */
bool rbuffer_discard(rbuffer *self);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_RBUFFER_H_ */
