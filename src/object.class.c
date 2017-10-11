#include <assert.h>

#include <util/memory.h>

#include <object.h>
#include <object.class.h>

void *init(void *self, const class *cls, ...)
{
    void *obj;
    va_list va;
    assert(cls != NULL);
    // Initialise class, if needed
    if (cls->name == NULL) {
        cls->class_init((class *)cls);
    }
    // Initialise object
    const object_mt *mt = (object_mt *)mt_of_class(cls, Object);
    va_start(va, cls);
    obj = mt->vinit(self, &va);
    va_end(va);
    return obj;
}

const class *class_of(const void *self)
{
    assert(self != NULL);
    return ((object *)self)->cls;
}

bool isinstance(const void *self, const void *cls)
{
    return false;
}

const char *name_of(const void *self)
{
    return class_of(self)->name;
}

size_t size_of(const void *self)
{
    return class_of(self)->size;
}

const void *mt_of(const void *self, const void *subcls)
{
    return mt_of_class(class_of(self), subcls);
}

void destroy(void *self)
{
    const object_mt *mt = mt_of(self, Object);
    mt->destroy(self);
}

size_t to_cstr(void *self, char *cstr, size_t size)
{
    return 0;
}

void print(void *self)
{
    const object_mt *mt = mt_of(self, Object);
    mt->print(self);
}

static const class *_class_init(class *cls)
{
    // Initialise method table of Object class
    static const object_mt mt = {
        .vinit = (vinit_cb)object_vinit,
        .destroy = (destroy_cb)object_destroy,
        .to_cstr = (to_cstr_cb)object_to_cstr,
        .print = (print_cb)object_print
    };
    static vtable vts[1];
    vts[0].cls = cls;
    vts[0].mt = (method_cb *)&mt;
    // Initialise class
    return class_init(cls, "object", sizeof(object), ARRAY_SIZE(vts), vts);
}

static class _Object = {
    .class_init = _class_init,
    .name = NULL
    // Everthing else will be initialised by init_class method.
};

const class *Object = &_Object;
