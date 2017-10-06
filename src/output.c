#include <util/print.h>

#include <output.h>

output *output_init(output *self)
{
    object_init(&self->obj, Output);
    return self;
}

output *output_vinit(output *self, va_list *va)
{
    return output_init(self);
}

void output_destroy(output *self)
{
    object_destroy(&self->obj);
}

size_t output_write(output *self, const char *data, size_t size)
{
    return fwrite(data, 1, size, stdout);
}

int output_format(output *self, const char *fmt, ...)
{
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = output_vformat(self, fmt, &va);
    va_end(va);
    return ret;
}

int output_vformat(output *self, const char *fmt, va_list *va)
{
    return vprintf(fmt, *va);
}
