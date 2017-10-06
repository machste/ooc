#include <output.class.h>

size_t write(void *self, const char *data, size_t size)
{
    const output_mt *mt = mt_of(self, &Output);
    return mt->write(self, data, size);
}

int format(void *self, const char *fmt, ...)
{
    const output_mt *mt = mt_of(self, &Output);
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

const class Output = {
    .name = "output",
    .size = sizeof(output),
    .mt = &_OutputMt,
    .super = &Object,
    .vmts = _OutputVmts
};
