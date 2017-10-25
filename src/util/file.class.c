#include <util/memory.h>

#include <util/file.h>

static const class *_class_init(class *cls)
{
    // Initialise method table of File class
    static const file_mt mt = {
        .open = (open_cb)file_open,
        .close = (close_cb)file_close
    };
    // Initialise virtual tables
    static const input_mt input_vmt = {
        .read = (read_cb)file_read,
        .vscan = (vscan_cb)file_vscan,
        .discard = (discard_cb)file_flush
    };
    static const output_mt output_vmt = {
        .write = (write_cb)file_write,
        .vformat = (vformat_cb)file_vformat,
        .flush = (flush_cb)file_flush
    };
    static const object_mt object_vmt = {
        .vinit = (vinit_cb)file_vinit,
        .destroy = (destroy_cb)file_destroy,
        .put = (put_cb)object_put,
        .to_cstr = (to_cstr_cb)object_to_cstr
    };
    static vtable vts[4];
    vts[0].cls = cls;
    vts[0].mt = (method_cb *)&mt;
    // Input viratual table
    vts[1].cls = Input;
    vts[1].mt = (method_cb *)&input_vmt;
    // Output virtual table
    vts[2].cls = Output;
    vts[2].mt = (method_cb *)&output_vmt;
    // Object virtual table
    vts[3].cls = Object;
    vts[3].mt = (method_cb *)&object_vmt;
    // Initialise class
    return class_init(cls, "file", sizeof(file), ARRAY_SIZE(vts), vts);
}

static class _File = {
    .class_init = _class_init,
    .name = NULL
    // Everthing else will be initialised by init_class method.
};

const class *File = &_File;
