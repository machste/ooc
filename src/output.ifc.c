#include <object.class.h>
#include <util/assert.h>

#include <output.ifc.h>

size_t write(void *self, const char *data, size_t size)
{
    const output_mt *mt = mt_of(self, Output);
    ASSERT(mt->write != NULL);
    return mt->write(self, data, size);
}

int format(void *self, const char *fmt, ...)
{
    const output_mt *mt = mt_of(self, Output);
    int ret;
    ASSERT(mt->vformat != NULL);
    va_list va;
    va_start(va, fmt);
    ret = mt->vformat(self, fmt, &va);
    va_end(va);
    return ret;
}

int vformat(void *self, const char *fmt, va_list *va)
{
    const output_mt *mt = mt_of(self, Output);
    ASSERT(mt->vformat != NULL);
    return mt->vformat(self, fmt, va);
}

bool flush(void *self)
{
    const output_mt *mt = mt_of(self, Output);
    ASSERT(mt->flush != NULL);
    return mt->flush(self);
}

static const class *_ifc_init(class *cls)
{
    // Initialise interface
    return class_init(cls, "output", 0, 0, NULL);
}

static class _Output = {
    .class_init = _ifc_init,
    .name = NULL
    // Everthing else will be initialised by _ifc_init method.
};

const class *Output = &_Output;
