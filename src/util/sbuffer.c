#include <string.h>
#include <stdio.h>

#include <util/sbuffer.h>

sbuffer *sbuffer_init(sbuffer *self, const class *cls, char *data, size_t size)
{
    object_init(self, cls);
    self->size = size;
    self->data = data;
    return self;
}

sbuffer *sbuffer_vinit(sbuffer *self, const class *cls, va_list *va)
{
    char *data = va_arg(*va, char *);
    size_t size = va_arg(*va, size_t);
    return sbuffer_init(self, cls, data, size);
}

int sbuffer_put(sbuffer *self, output *out)
{
    int size = 0, n;
    n = format(out, "<%s, len: %zu, data: ", name_of(self), len(self));
    if (n < 0)
        return -1;
    size += n;
    n = write(out, "-->", 3);
    if (n < 0)
        return -1;
    size += n;
    return size;
}

size_t sbuffer_len(sbuffer *self)
{
    return self->size;
}

char *sbuffer_get_at(sbuffer *self, int index)
{
    index = Container_fixup_index(len(self), index);
    if (index >= 0) {
        return self->data + index;
    } else {
        return NULL;
    }
}

char *sbuffer_set_at(sbuffer *self, int index, char *item)
{
    char *byte = get_at(self, index);
    if (byte != NULL) {
        *byte = *item;
    }
    return byte;
}

void sbuffer_clear(sbuffer *self)
{
    // Nothing to do here
}

size_t sbuffer_read(sbuffer *self, char *data, size_t size)
{
    if (size > self->size) {
        size = self->size;
    }
    memcpy(data, self->data, size);
    return size;
}

size_t sbuffer_write(sbuffer *self, const char *data, size_t size)
{
    if (size > self->size) {
        size = self->size;
    }
    memcpy(self->data, data, size);
    return size;    
}

int sbuffer_scan(sbuffer *self, const char *fmt, ...)
{
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = vscan(self, fmt, &va);
    va_end(va);
    return ret;    
}

int sbuffer_vscan(sbuffer *self, const char *fmt, va_list *va)
{
    return vsscanf(self->data, fmt, *va);
}

int sbuffer_format(sbuffer *self, const char *fmt, ...)
{
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = vformat(self, fmt, &va);
    va_end(va);
    return ret;    
}

int sbuffer_vformat(sbuffer *self, const char *fmt, va_list *va)
{
    return vsnprintf(self->data, self->size, fmt, *va);
}

bool sbuffer_discard(sbuffer *self)
{
    // Nothing to do here
    return true;
}

bool sbuffer_flush(sbuffer *self)
{
    // Nothing to do here
    return true;
}
