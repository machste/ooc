#include <util/memory.h>

#include <output.h>
#include <output.class.h>

size_t write(void *self, const char *data, size_t size)
{
    const output_mt *mt = mt_of(self, Output);
    return mt->write(self, data, size);
}

int format(void *self, const char *fmt, ...)
{
    const output_mt *mt = mt_of(self, Output);
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = mt->vformat(self, fmt, &va);
    va_end(va);
    return ret;
}

int vformat(void *self, const char *fmt, va_list *va)
{
    const output_mt *mt = mt_of(self, Output);
    return mt->vformat(self, fmt, va);
}

static const class *_class_init(class *cls)
{
    // Initialise method table of Output class
    static const output_mt mt = {
        .write = (write_cb)output_write,
        .vformat = (vformat_cb)output_vformat
    };
    // Initialise virtual tables
    static const object_mt object_vmt = {
        .vinit = (vinit_cb)output_vinit,
        .destroy = (destroy_cb)output_destroy,
        .put = (put_cb)object_put,
        .take = (take_cb)object_take,
        .to_cstr = (to_cstr_cb)object_to_cstr
    };
    static vtable vts[2];
    vts[0].cls = cls;
    vts[0].mt = (method_cb *)&mt;
    vts[1].cls = Object;
    vts[1].mt = (method_cb *)&object_vmt;
    // Initialise class
    return class_init(cls, "output", sizeof(output), ARRAY_SIZE(vts), vts);
}

static class _Output = {
    .class_init = _class_init,
    .name = NULL
    // Everthing else will be initialised by init_class method.
};

const class *Output = &_Output;
