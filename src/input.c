#include <util/print.h>

#include <input.h>

input *input_init(input *self, const class *cls)
{
    object_init(&self->obj, cls);
    return self;
}

input *input_vinit(input *self, const class *cls, va_list *va)
{
    return input_init(self, cls);
}

void input_destroy(input *self)
{
    object_destroy(&self->obj);
}

size_t input_read(input *self, char *data, size_t size)
{
    return fread(data, 1, size, stdin);
}

int input_scan(input *self, const char *fmt, ...)
{
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = input_vscan(self, fmt, &va);
    va_end(va);
    return ret;
}

int input_vscan(input *self, const char *fmt, va_list *va)
{
    return vscanf(fmt, *va);
}
