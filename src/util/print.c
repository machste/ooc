#include <stdio.h>

#include <output.h>
#include <util/memory.h>
#include <util/log.h> // TODO: Remote it!

#include <util/print.h>

static output _stdoutput = { .obj = { .cls = NULL } };

static output *_get_stdoutput(void)
{
    output *out;

    if(_stdoutput.obj.cls == NULL) {
        out = init(&_stdoutput, Output);
    } else {
        out = &_stdoutput;
    }
    return out;
}

void print(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    vprint(fmt, va);
    va_end(va);
}

void vprint(const char *fmt, va_list va)
{
    const char *copy_of_fmt = fmt;
    va_list copy_of_va;
    // Make a copy of the original variable argument (va) parameter
    va_copy(copy_of_va, va);
    /* Parse the format string */
    while (*fmt != '\0') {
        // If the current character of 'fmt' is not a '%' or "%%" ...
        if ((*fmt != '%') || (*++fmt == '%')) {
            // ... it is not relevat, skip it.
            fmt++;
            continue;
        }
        Log_debug("vprint: %c\n", *fmt);
        
        // Advance 'fmt' to the next character.
        fmt++;
    }
    // Print
    vprintf(copy_of_fmt, copy_of_va);
    puts("");
}
