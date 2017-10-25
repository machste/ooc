#include <stdlib.h>
#include <string.h>

#include <util/file.h>

file *file_init(file *self, const class *cls, const char *path)
{
    object_init(self, cls);
    self->path = strdup(path);
    self->file = NULL;
    return self;
}

file *file_vinit(file *self, const class *cls, va_list *va)
{
    const char *path = va_arg(*va, const char *);
    return file_init(self, cls, path);
}

void file_destroy(file *self)
{
    if (self->file != NULL) {
        close(self);
    }
    free(self->path);
    object_destroy(self);
}

bool file_open(file *self, const char *mode)
{
    self->file = fopen(self->path, mode);
    return self->file != NULL;
}

bool file_close(file *self)
{
    self->file = NULL;
    return fclose(self->file) == 0;
}

size_t file_read(file *self, char *data, size_t size)
{
    return fread(data, 1, size, self->file);
}

size_t file_write(file *self, const char *data, size_t size)
{
    return fwrite(data, 1, size, self->file);
}

int file_scan(file *self, const char *fmt, ...)
{
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = vscan(self, fmt, &va);
    va_end(va);
    return ret;
}

int file_vscan(file *self, const char *fmt, va_list *va)
{
    return vfscanf(self->file, fmt, *va);
}

int file_format(file *self, const char *fmt, ...)
{
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = vformat(self, fmt, &va);
    va_end(va);
    return ret;
}

int file_vformat(file *self, const char *fmt, va_list *va)
{
    return vfprintf(self->file, fmt, *va);
}

bool file_flush(file *self)
{
    return fflush(self->file) == 0;
}
