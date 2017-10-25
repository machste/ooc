#include <util/file.h>

#include <util/print.h>

static file _stdoutput = { .obj = { .cls = NULL } };

static file *_get_stdoutput(void)
{
    file *out;

    if(_stdoutput.obj.cls == NULL) {
        out = init(&_stdoutput, File, "<stdout>");
        out->file = stdout;
    } else {
        out = &_stdoutput;
    }
    return out;
}

void print(void *obj)
{
    file *out = _get_stdoutput();
    put(obj, out);
    write(out, "\n", 1);
}
