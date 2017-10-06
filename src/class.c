#include <assert.h>

#include <class.h>

bool issubclass(const class *cls, const class *subcls)
{
    const class *_cls = cls;
    while (_cls != NULL) {
        if (_cls == subcls) {
            return true;
        }
        _cls = _cls->super;
    }
    return false;
}

const void *mt_of_class(const class *cls, const class *subcls)
{
    const class *_cls = cls;
    assert(_cls != NULL);
    if (_cls == subcls) {
        return _cls->mt;
    } else {
        unsigned int i = 0;
        _cls = _cls->super;
        while (_cls != NULL) {
            if (_cls == subcls) {
                return cls->vmts[i];
            }
            _cls = _cls->super;
            i++;
        }
        assert(_cls != NULL);
    }
    return NULL;
}
