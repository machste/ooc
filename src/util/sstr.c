#include <string.h>

#include <util/rbuffer.h>

#include <util/sstr.h>

sstr *_vinit(sstr *self, const class *cls, char *data, size_t size,
        const char *fmt, va_list *fmt_va)
{
    sbuffer_init(&self->sbuf, cls, data, size);
    vformat(self, fmt, fmt_va);
    return self;
}

sstr *sstr_init(sstr *self, const class *cls, char *data, size_t size,
        const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    _vinit(self, cls, data, size, fmt, &va);
    va_end(va);
    return self;
}

sstr *sstr_vinit(sstr *self, const class *cls, va_list *va)
{
    char *data = va_arg(*va, char *);
    size_t size = va_arg(*va, size_t);
    const char *fmt = va_arg(*va, const char *);
    return _vinit(self, cls, data, size, fmt, va);
}

int sstr_put(sstr *self, output *out)
{
    size_t length = len(self);
    if (length > 0) {
        return write(out, cstr(self), length);
    } else {
        return 0;
    }
}

size_t sstr_len(sstr *self)
{
    if (self->sbuf.data != NULL) {
        return strlen(self->sbuf.data);
    } else {
        return 0;
    }
}

void sstr_clear(sstr *self)
{
    if (self->sbuf.size > 0) {
        self->sbuf.data[0] = '\0';
    }
}

size_t sstr_read(sstr *self, char *data, size_t size)
{
    if (size > len(self)) {
        size = len(self);
    }
    memcpy(data, self->sbuf.data, size);
    return size;
}

size_t sstr_write(sstr *self, const char *data, size_t size)
{
    size_t i;
    if (size > self->sbuf.size - 1) {
        size = self->sbuf.size - 1;
    }
    for (i = 0; i < size && data[i] != '\0'; i++) {
        self->sbuf.data[i] = data[i];
    }
    self->sbuf.data[i] = '\0';
    return i;
}

const char *sstr_cstr(sstr *self)
{
    return self->sbuf.data;
}
