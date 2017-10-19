#include <util/memory.h>

#include <util/rbuffer.h>

static const class *_class_init(class *cls)
{
    // Initialise virtual tables
    static const input_mt input_vmt = {
        .read = (read_cb)rbuffer_read,
        .vscan = (vscan_cb)rbuffer_vscan,
        .discard = (discard_cb)rbuffer_discard
    };
    static const output_mt output_vmt = {
        .write = (write_cb)rbuffer_write,
        .vformat = (vformat_cb)rbuffer_vformat,
        .flush = (flush_cb)sbuffer_flush
    };
    static const container_mt container_vmt = {
        .len = (len_cb)rbuffer_len,
        .get_at = (get_at_cb)rbuffer_get_at,
        .set_at = (set_at_cb)sbuffer_set_at,
        .clear = (clear_cb)rbuffer_clear
    };
    static const object_mt object_vmt = {
        .vinit = (vinit_cb)rbuffer_vinit,
        .destroy = (destroy_cb)object_destroy,
        .put = (put_cb)object_put,
        .to_cstr = (to_cstr_cb)object_to_cstr
    };
    static vtable vts[5];
    // Method table of RBuffer class
    vts[0].cls = cls;
    vts[0].mt = NULL; // No methods for rbuffer
    // Virtual method table of Input class
    vts[1].cls = Input;
    vts[1].mt = (method_cb *)&input_vmt;
    // Virtual method table of Output class
    vts[2].cls = Output;
    vts[2].mt = (method_cb *)&output_vmt;
    // Virtual method table of Container interface
    vts[3].cls = Container;
    vts[3].mt = (method_cb *)&container_vmt;
    // Virtual method table of Object class
    vts[4].cls = Object;
    vts[4].mt = (method_cb *)&object_vmt;
    // Initialise class
    return class_init(cls, "rbuffer", sizeof(rbuffer), ARRAY_SIZE(vts), vts);
}

static class _RBuffer = {
    .class_init = _class_init,
    .name = NULL
    // Everthing else will be initialised by init_class method.
};

const class *RBuffer = &_RBuffer;
