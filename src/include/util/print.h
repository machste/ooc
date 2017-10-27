#ifndef _UTIL_PRINT_H_
#define _UTIL_PRINT_H_

#include <stdarg.h>

/**
 * @brief Print an Object to the Standard Output
 */
void print(const char *fmt, ...);
void vprint(const char *fmt, va_list va);

#endif /* _UTIL_PRINT_H_ */
