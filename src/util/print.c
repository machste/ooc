#include <output.h>

#include <util/print.h>

static output _stdoutput = { .obj = { .cls = NULL } };

static output *_get_stdoutput(void)
{
    output *out;

    if(_stdoutput.obj.cls == NULL) {
        out = init(&_stdoutput, Output);
    } else {
        out = &_stdoutput;
    }
    return out;
}

void print(void *obj)
{
    output *out = _get_stdoutput();
    put(obj, out);
    puts("");
}
