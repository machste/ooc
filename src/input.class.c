#include <input.class.h>

size_t read(void *self, char *data, size_t size)
{
    const input_mt *mt = mt_of(self, &Input);
    return mt->read(self, data, size);
}

int scan(void *self, const char *fmt, ...)
{
    const input_mt *mt = mt_of(self, &Input);
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = mt->vscan(self, fmt, &va);
    va_end(va);
    return ret;
}

static const object_mt _ObjectVmt = {
    .vinit = (vinit_cb)input_vinit,
    .destroy = (destroy_cb)input_destroy,
    .to_cstr = (to_cstr_cb)object_to_cstr,
    .print = (print_cb)object_print,
};

static const void *_InputVmts[] = {
    &_ObjectVmt
};

static const input_mt _InputMt = {
    .read = (read_cb)input_read,
    .vscan = (vscan_cb)input_vscan
};

static const class *_class_init(void)
{
    return class_init(Input, "input", sizeof(input), &_InputMt, Object,
            _InputVmts);
}

static class _Input = {
    .class_init = _class_init,
    .name = NULL
    // Everthing else will be initialised by init_class method.
};

const class *Input = &_Input;
