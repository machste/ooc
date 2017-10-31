/**
 * @file    util/sstr.class.h
 *
 * @brief   Static String Class
 */
#ifndef _UTIL_SSTR_CLASS_H_
#define _UTIL_SSTR_CLASS_H_

#include <class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Static String Class
 */
extern const class *SStr;

/**
 * @brief Static String Methods
 */
typedef const char *(*cstr_cb)(void *self);

/**
 * @brief Method Table of Static String
 */
typedef struct sstr_mt {
    cstr_cb cstr;
} sstr_mt;

/**
 * @brief Get C-String from Static String
 */
const char *cstr(void *self);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_SSTR_CLASS_H_ */
