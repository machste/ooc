#ifndef _UTIL_MEMORY_H_
#define _UTIL_MEMORY_H_

#define ARRAY_SIZE( _array ) (sizeof(_array) / sizeof(_array)[0])

#define OFFSETOF(type, member) ((size_t) &((type *)0)->member)

#define STRUCT_OF(ptr, type, member) ({ \
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - OFFSETOF(type,member) );})

#define MALLOC_STRUCT(type) ((type *)MALLOC(sizeof(type)))

#if defined(WIPLA_USE_ICALL_HEAP)

/* Use memory allocation function of the ICall library */

#include <icall.h>

#define MALLOC(size)        ICall_malloc(size)
#define FREE(ptr)           ICall_free(ptr)
#define REALLOC(ptr, size)  _icall_realloc(ptr, size)

void *_icall_realloc(void *old, size_t size);

#elif defined(WIPLA_USE_XDC_RUNTIME_HEAP)

/* Use memory allocation function of XDC runtime library */

#include <stddef.h>

#define MALLOC(size)        _xdc_malloc(size)
#define FREE(ptr)           _xdc_free(ptr)
#define REALLOC(ptr, size)  _xdc_realloc(ptr, size)

void *_xdc_malloc(size_t size);

void _xdc_free(void *ptr);

void *_xdc_realloc(void *ptr, size_t size);

#else

/* Use ordinary functions from the <stdlib.h> */

#include <stdlib.h>

#define MALLOC(size)        malloc(size)
#define FREE(ptr)           free(ptr)
#define REALLOC(ptr, size)  realloc(ptr, size)

#endif

#endif /* _UTIL_PRINTF_H_ */
