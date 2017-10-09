#include <assert.h>

#include <class.h>

const class *class_init(class *cls, const char *name, size_t size,
        size_t vts_len, const vtable *vts)
{
    cls->name = name;
    cls->size = size;
    // Initialise all super classes (multiple inheritance)
    cls->vtables_len = vts_len;
    for (int i = 0; i < vts_len; i++) {
        const vtable *vt = vts + i;
        assert(vt != NULL && vt->cls != NULL);
        // Initialise super class, if needed
        if (vt->cls->name == NULL) {
            vt->cls->class_init((class *)vt->cls);
        }
    }
    cls->vtables = vts;
    return cls;

}

static const vtable *_vtable(const class *cls, const class *subcls)
{
    assert(cls != NULL);
    for (int i = 0; i < cls->vtables_len; i++) {
        if (cls->vtables[i].cls == subcls) {
            return cls->vtables + i;
        }
    }
    return NULL;
}

bool issubclass(const class *cls, const class *subcls)
{
    return _vtable(cls, subcls) != NULL;
}

const method_table mt_of_class(const class *cls, const class *subcls)
{
    const vtable *vt = _vtable(cls, subcls);
    assert(vt != NULL);
    return vt->mt;
}
