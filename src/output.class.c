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

static const object_mt _ObjectVmt = {
    .vinit = (vinit_cb)output_vinit,
    .destroy = (destroy_cb)output_destroy,
    .to_cstr = (to_cstr_cb)object_to_cstr,
    .print = (print_cb)object_print,
};

static const void *_OutputVmts[] = {
    &_ObjectVmt
};

static const output_mt _OutputMt = {
    .write = (write_cb)output_write,
    .vformat = (vformat_cb)output_vformat
};

static const class *_class_init(void)
{
    return class_init(Output, "output", sizeof(output), &_OutputMt, Object,
            _OutputVmts);
}

static class _Output = {
    .class_init = _class_init,
    .name = NULL
    // Everthing else will be initialised by init_class method.
};

const class *Output = &_Output;
