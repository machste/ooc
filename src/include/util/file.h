/**
 * @file    util/file.h
 *
 * @brief   File Object
 */
#ifndef _UTIL_FILE_H_
#define _UTIL_FILE_H_

#include <stdio.h>

#include <object.h>
#include <input.ifc.h>
#include <output.ifc.h>
#include <util/file.class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief File Object
 */
typedef struct file {
    object obj;
    char *path;
    FILE *file;
} file;

/**
 * @brief File specific implementation of 'init()'
 */
file *file_init(file *self, const class *cls, const char *path);
file *file_vinit(file *self, const class *cls, va_list *va);

/**
 * @brief File specific implementation of 'destroy()'
 */
void file_destroy(file *self);

/**
 * @brief File specific implementation of 'open()'
 */
bool file_open(file *self, const char *mode);

/**
 * @brief File specific implementation of 'close()'
 */
bool file_close(file *self);

/**
 * @brief File specific implementation of 'read()'
 */
size_t file_read(file *self, char *data, size_t size);

/**
 * @brief File specific implementation of 'write()'
 */
size_t file_write(file *self, const char *data, size_t size);

/**
 * @brief File specific implementation of 'scan()'
 */
int file_scan(file *self, const char *fmt, ...);
int file_vscan(file *self, const char *fmt, va_list *va);

/**
 * @brief File specific implementation of 'format()'
 */
int file_format(file *self, const char *fmt, ...);
int file_vformat(file *self, const char *fmt, va_list *va);

/**
 * @brief File specific implementation of 'flush()'
 */
bool file_flush(file *self);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_FILE_H_ */
