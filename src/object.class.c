#include <stdarg.h>

#include <object.h>

void *init(void *self, const void *cls, ...)
{
    void *obj;
    va_list va;
    const object_class *object_cls = cls;
    va_start(va, cls);
    obj = object_cls->vinit(self, object_cls, &va);
    va_end(va);
    return obj;
}

void destroy(void *self)
{
    const object_class *cls = class_of(self);
    cls->destroy(self);
}

const void *class_of(const void *self)
{
    return ((object *)self)->object_cls;
}

const char *name_of(const void *self)
{
    return ((object *)self)->object_cls->cls.name;
}

size_t size_of(const void *self)
{
    return ((object *)self)->object_cls->cls.size;
}

bool isinstance(const void *self, const void *cls)
{
    return false;
}

size_t to_cstr(void *self, char *cstr, size_t size)
{
    return 0;
}

void print(void *self)
{
    const object_class *cls = class_of(self);
    cls->print(self);
}
