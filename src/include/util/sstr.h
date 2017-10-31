/**
 * @file    util/sstr.h
 *
 * @brief   Static String Object
 */
#ifndef _UTIL_SSTR_H_
#define _UTIL_SSTR_H_

#include <util/sbuffer.h>
#include <util/sstr.class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Static String Object
 */
typedef struct sstr {
    sbuffer sbuf;
} sstr;

/**
 * @brief Static String specific implementation of init()
 */
sstr *sstr_init(sstr *self, const class *cls, char *data, size_t size,
        const char *fmt, ...);
sstr *sstr_vinit(sstr *self, const class *cls, va_list *va);

/**
 * @brief Static String specific implementation of put()
 */
int sstr_put(sstr *self, output *out);

/**
 * @brief Static String specific implementation of len()
 *
 * @return Length of the string (without the terminating null byte)
 */
size_t sstr_len(sstr *self);

/**
 * @brief Static String specific implementation of clear()
 */
void sstr_clear(sstr *self);

/**
 * @brief Static String specific implementation of read()
 */
size_t sstr_read(sstr *self, char *data, size_t size);

/**
 * @brief Static String specific implementation of write()
 */
size_t sstr_write(sstr *self, const char *data, size_t size);

/**
 * @brief Static String specific implementation of clear()
 */
const char *sstr_cstr(sstr *self);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_SSTR_H_ */
