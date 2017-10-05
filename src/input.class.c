#include <input.h>

size_t read(void *self, char *data, size_t size)
{
    const input_class *cls = class_of(self);
    return cls->read(self, data, size);
}

int scan(void *self, const char *fmt, ...)
{
    const input_class *cls = class_of(self);
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = cls->vscan(self, fmt, &va);
    va_end(va);
    return ret;
}
