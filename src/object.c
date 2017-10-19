#include <output.ifc.h>
#include <util/rbuffer.h>

#include <object.h>

object *object_init(object *self, const class *cls)
{
    self->cls = cls;
    return self;
}

object *object_vinit(object *self, const class *cls, va_list *va)
{
    return object_init(self, cls);
}

void object_destroy(object *self)
{
    // Nothing to do here.
}

int object_put(object *self, output *out) {
    return format(out, "<%s at %p, size: %zu>", name_of(self), self,
            size_of(self));
}

int object_take(object *self, input *in) {
    return -1;
}

size_t object_to_cstr(object *self, char *cstr, size_t size)
{
    size_t ret;
    rbuffer buf;
    init(&buf, RBuffer, cstr, size);
    ret = put(self, &buf);
    destroy(&buf);
    return ret;
}
