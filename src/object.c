#include <util/print.h> // TODO: Remove it
#include <util/log.h> // TODO: Remove it
#include <output.h>

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

    // TODO: Use _put_as_cstr here.
    return snprintf(cstr, size, "<%s at %p, size: %zu>", name_of(self), self,
            size_of(self));
    /*
    size_t len = 0;
    char *cstr = NULL;
    len = object_to_cstr(self, cstr, len);
    cstr = MALLOC(len + 1);
    if (cstr != NULL) {
        object_to_cstr(self, cstr, len + 1);
        puts(cstr);
        FREE(cstr);
    } else {
        Log_error("Out of memory!\n");
    }
    */
}

void object_print(object *self)
{
    object_put(self, &stdoutput);
    puts("");
}
