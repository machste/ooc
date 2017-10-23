#ifndef _UTIL_MEMORY_H_
#define _UTIL_MEMORY_H_

#include <stdlib.h>

#define ARRAY_SIZE( _array ) (sizeof(_array) / sizeof(_array)[0])

#define OFFSETOF(type, member) ((size_t) &((type *)0)->member)

#define STRUCT_OF(ptr, type, member) ({ \
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - OFFSETOF(type,member) );})

#define MALLOC_STRUCT(type) ((type *)MALLOC(sizeof(type)))

#define MALLOC(size) malloc(size)
#define FREE(ptr) free(ptr)
#define REALLOC(ptr, size) realloc(ptr, size)

#endif /* _UTIL_MEMORY_H_ */
