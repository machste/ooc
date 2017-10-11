#include <util/memory.h>

#include <input.h>
#include <input.class.h>

size_t read(void *self, char *data, size_t size)
{
    const input_mt *mt = mt_of(self, Input);
    return mt->read(self, data, size);
}

int scan(void *self, const char *fmt, ...)
{
    const input_mt *mt = mt_of(self, Input);
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = mt->vscan(self, fmt, &va);
    va_end(va);
    return ret;
}

int vscan(void *self, const char *fmt, va_list *va)
{
    const input_mt *mt = mt_of(self, Input);
    return mt->vscan(self, fmt, va);
}

static const class *_class_init(class *cls)
{
    // Initialise method table of Input class
    static const input_mt mt = {
        .read = (read_cb)input_read,
        .vscan = (vscan_cb)input_vscan
    };
    // Initialise virtual tables
    static const object_mt object_vmt = {
        .vinit = (vinit_cb)input_vinit,
        .destroy = (destroy_cb)input_destroy,
        .to_cstr = (to_cstr_cb)object_to_cstr,
        .print = (print_cb)object_print,
    };
    static vtable vts[2];
    vts[0].cls = cls;
    vts[0].mt = (method_cb *)&mt;
    vts[1].cls = Object;
    vts[1].mt = (method_cb *)&object_vmt;
    // Initialise class
    return class_init(cls, "input", sizeof(input), ARRAY_SIZE(vts), vts);
}

static class _Input = {
    .class_init = _class_init,
    .name = NULL
    // Everthing else will be initialised by init_class method.
};

const class *Input = &_Input;
