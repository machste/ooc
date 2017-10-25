/**
 * @file    util/file.class.h
 *
 * @brief   File Class
 */
#ifndef _UTIL_FILE_CLASS_H_
#define _UTIL_FILE_CLASS_H_

#include <class.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief File Class
 */
extern const class *File;

/**
 * Forward Declaration of the 'file' Object
 */
typedef struct file file;

/**
 * @brief File Methods
 */
typedef bool (*open_cb)(file *self, const char *mode);
typedef bool (*close_cb)(file *self);

/**
 * @brief Method Table of File
 */
typedef struct file_mt {
    open_cb open;
    close_cb close;
} file_mt;

/**
 * @brief Open a File
 *
 * Open the file with the given 'mode', see 'fopen()' for more details.
 *
 * @return True for a successfully opened file otherwise false
 */
bool open(file *self, const char *mode);

/**
 * @brief Close a File
 *
 * Flush all buffered output data using 'flush()' and close the underlying
 * file, see also 'fclose()'.
 *
 * @return True when the file was closed successfully otherwise false.
 */
bool close(file *self);

#ifdef __cplusplus
}
#endif

#endif /* _UTIL_FILE_CLASS_H_ */
