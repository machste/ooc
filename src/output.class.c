#include <output.h>

size_t write(void *self, const char *data, size_t size)
{
    const output_class *cls = class_of(self);
    return cls->write(self, data, size);
}

int format(void *self, const char *fmt, ...)
{
    const output_class *cls = class_of(self);
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = cls->vformat(self, fmt, &va);
    va_end(va);
    return ret;
}
