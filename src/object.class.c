#include <stdarg.h>
#include <assert.h>

#include <object.class.h>

void *init(void *self, const class *cls, ...)
{
    void *obj;
    va_list va;
    assert(cls != NULL);
    // Initialise class, if needed
    if (cls->name == NULL) {
        cls->class_init();
    }
    // Initialise object
    const object_mt *mt = mt_of_class(cls, Object);
    va_start(va, cls);
    obj = mt->vinit(self, cls, &va);
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

static const object_mt _ObjectMt = {
    .vinit = (vinit_cb)object_vinit,
    .destroy = (destroy_cb)object_destroy,
    .to_cstr = (to_cstr_cb)object_to_cstr,
    .print = (print_cb)object_print
};

static const class *_class_init(void)
{
    return class_init(Object, "object", sizeof(object), &_ObjectMt, NULL, NULL);
}

static class _Object = {
    .class_init = _class_init,
    .name = NULL
    // Everthing else will be initialised by init_class method.
};

const class *Object = &_Object;