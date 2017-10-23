#include <util/assert.h>
#include <util/memory.h>

#include <object.h>

void *init(void *self, const class *cls, ...)
{
    void *obj;
    va_list va;
    ASSERT(cls != NULL);
    // Initialise class, if needed
    if (cls->name == NULL) {
        ASSERT(cls->class_init != NULL);
        cls->class_init((class *)cls);
    }
    // Initialise object
    const object_mt *mt = (object_mt *)mt_of_class(cls, Object);
    va_start(va, cls);
    ASSERT(mt->vinit != NULL);
    obj = mt->vinit(self, cls, &va);
    va_end(va);
    return obj;
}

void destroy(void *self)
{
    const object_mt *mt = mt_of(self, Object);
    ASSERT(mt->destroy);
    mt->destroy(self);
}

const class *class_of(const void *self)
{
    ASSERT(self != NULL);
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

int put(void *self, void *out)
{
    const object_mt *mt = mt_of(self, Object);
    ASSERT(mt->put);
    return mt->put(self, out);
}

int take(void *self, void *in)
{
    const object_mt *mt = mt_of(self, Object);
    ASSERT(mt->take);
    return mt->take(self, in);
}

size_t to_cstr(void *self, char *cstr, size_t size)
{
    const object_mt *mt = mt_of(self, Object);
    ASSERT(mt->to_cstr);
    return mt->to_cstr(self, cstr, size);
}

static const class *_class_init(class *cls)
{
    // Initialise method table of Object class
    static const object_mt mt = {
        .vinit = (vinit_cb)object_vinit,
        .destroy = (destroy_cb)object_destroy,
        .put = (put_cb)object_put,
        .take = (take_cb)object_put,
        .to_cstr = (to_cstr_cb)object_to_cstr
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
