#ifndef _UTIL_PRINT_H_
#define _UTIL_PRINT_H_

#ifdef WIPLA_USE_XDC_RUNTIME
#include <xdc/runtime/System.h>
// Define aliases for using normal printf-like functions
#define printf(fmt, ...)           System_printf(fmt, ##__VA_ARGS__)
#define snprintf(buf, n, fmt, ...) System_snprintf(buf, n, fmt, ##__VA_ARGS__)
#define vprintf(fmt, va)           System_vprintf(fmt, va)
#define vsnprintf(buf, n, fmt, va) System_vsnprintf(buf, n, fmt, va)
#else
// Use ordinary functions from the <stdio.h>
#include <stdio.h>
#endif /* WIPLA_USE_XDC_TOOLS */

#endif /* _UTIL_PRINT_H_ */
