#include <object.class.h>
#include <util/assert.h>

#include <container.ifc.h>

int Container_fixup_index(size_t size, int index)
{
    // Handle negative indexes (e.g. -1 equals to the last index)
    if (index < 0) {
        index += size;
    }
    // Check the range
    if (index < 0 || index >= size) {
        // Index could not be corrected!
        index = -1;
    }
    return index;
}

size_t len(void *self)
{
    const container_mt *mt = mt_of(self, Container);
    ASSERT(mt->len != NULL);
    return mt->len(self);
}

void *get_at(void *self, int index)
{
    const container_mt *mt = mt_of(self, Container);
    ASSERT(mt->get_at != NULL);
    return mt->get_at(self, index);
}

void *set_at(void *self, int index, void *item)
{
    const container_mt *mt = mt_of(self, Container);
    ASSERT(mt->set_at != NULL);
    return mt->set_at(self, index, item);
}

void clear(void *self)
{
    const container_mt *mt = mt_of(self, Container);
    ASSERT(mt->clear != NULL);
    return mt->clear(self);
}

static const class *_ifc_init(class *cls)
{
    // Initialise interface
    return class_init(cls, "container", 0, 0, NULL);
}

static class _Container = {
    .class_init = _ifc_init,
    .name = NULL
    // Everthing else will be initialised by _ifc_init method.
};

const class *Container = &_Container;
