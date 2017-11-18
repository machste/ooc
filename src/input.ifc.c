#include <object.class.h>
#include <util/assert.h>

#include <input.ifc.h>

size_t read(input *self, char *data, size_t size)
{
    const input_mt *mt = mt_of((object *)self, Input);
    ASSERT(mt->read != NULL);
    return mt->read(self, data, size);
}

int scan(input *self, const char *fmt, ...)
{
    const input_mt *mt = mt_of((object *)self, Input);
    int ret;
    ASSERT(mt->vscan != NULL);
    va_list va;
    va_start(va, fmt);
    ret = mt->vscan(self, fmt, &va);
    va_end(va);
    return ret;
}

int vscan(input *self, const char *fmt, va_list *va)
{
    const input_mt *mt = mt_of((object *)self, Input);
    ASSERT(mt->vscan != NULL);
    return mt->vscan(self, fmt, va);
}

bool discard(input *self)
{
    const input_mt *mt = mt_of((object *)self, Input);
    ASSERT(mt->discard != NULL);
    return mt->discard(self);
}

static const class *_ifc_init(class *cls)
{
    // Initialise interface
    return class_init(cls, "input", 0, 0, NULL);
}

static class _Input = {
    .class_init = _ifc_init,
    .name = NULL
    // Everthing else will be initialised by _ifc_init method.
};

const class *Input = &_Input;
