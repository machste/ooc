#include <string.h>
#include <stdio.h>

#include <util/memory.h>

#include <util/rbuffer.h>

rbuffer *rbuffer_init(rbuffer *self, const class *cls, char *data, size_t size)
{
    sbuffer_init(&self->sbuf, cls, data, size);
    self->head = 0;
    self->foot = 0;
    return self;
}

rbuffer *rbuffer_vinit(rbuffer *self, const class *cls, va_list *va)
{
    char *data = va_arg(*va, char *);
    size_t size = va_arg(*va, size_t);
    return rbuffer_init(self, cls, data, size);
}

size_t rbuffer_len(rbuffer *self)
{
    if(self->head >= self->foot) {
        return self->head - self->foot;
    } else {
        return self->sbuf.size - self->foot + self->head;
    }
}

char *rbuffer_get_at(rbuffer *self, int index)
{
    char *byte = NULL;
    index = Container_fixup_index(len(self), index);
    if (index >= 0) {
        size_t idx = self->foot + index;
        if (idx > self->sbuf.size) {
            idx -= self->sbuf.size;
        }
        byte = self->sbuf.data + idx;
    }
    return byte;
}

void rbuffer_clear(rbuffer *self)
{
    self->head = 0;
    self->foot = 0;
}

size_t rbuffer_read(rbuffer *self, char *data, size_t size)
{
    size_t available_bytes = rbuffer_len(self);
    // Limit read size to available bytes
    if (size > available_bytes) {
        size = available_bytes;
    }
    if(self->head >= self->foot) {
        memcpy(data, self->sbuf.data + self->foot, size);
        self->foot += size;
    } else {
        size_t chunk_size = self->sbuf.size - self->foot;
        if (chunk_size > size) {
            memcpy(data, self->sbuf.data + self->foot, size);
            self->foot += size;
        } else {
            memcpy(data, self->sbuf.data + self->foot, chunk_size);
            self->foot = size - chunk_size;
            memcpy(data + chunk_size, self->sbuf.data, self->foot);
        }
    }
    return size;
}

void rbuffer_fill_empty(rbuffer *self, char c)
{
    if(self->head >= self->foot) {
        memset(self->sbuf.data + self->head, c, self->sbuf.size - self->head);
        memset(self->sbuf.data, c, self->foot);
    } else {
        memset(self->sbuf.data + self->head, c, self->foot - self->head);
    }
}

static size_t _free_bytes(rbuffer *self)
{
    size_t ret;
    if(self->head >= self->foot) {
        ret = self->sbuf.size - self->head + self->foot;
    } else {
        ret = self->foot - self->head;
    }
    /* Since it is not possible to decide if the buffer is full or empty, when
     * all the available bytes are used, there is one byte spared as guard. */
    return ret - 1;
}

size_t rbuffer_write(rbuffer *self, const char *data, size_t size)
{
    size_t free_bytes = _free_bytes(self);
    // Limit write size to free bytes
    if (size > free_bytes) {
        size = free_bytes;
    }
    if(self->head >= self->foot) {
        size_t chunk_size = self->sbuf.size - self->head;
        if (chunk_size > size) {
            memcpy(self->sbuf.data + self->head, data, size);
            self->head += size;
        } else {
            memcpy(self->sbuf.data + self->head, data, chunk_size);
            self->head = size - chunk_size;
            memcpy(self->sbuf.data, data + chunk_size, self->head);
        }
    } else {
        memcpy(self->sbuf.data + self->head, data, size);
        self->head += size;
    }
    return size;
}

int rbuffer_scan(rbuffer *self, const char *fmt, ...)
{
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = vscan(self, fmt, &va);
    va_end(va);
    return ret;
}

int rbuffer_vscan(rbuffer *self, const char *fmt, va_list *va)
{
    //TODO: Use the read() method to read from the proper place in the buffer.
    return vsscanf(self->sbuf.data, fmt, *va);
}

int rbuffer_format(rbuffer *self, const char *fmt, ...)
{
    int ret;
    va_list va;
    va_start(va, fmt);
    ret = vformat(self, fmt, &va);
    va_end(va);
    return ret;
}

int rbuffer_vformat(rbuffer *self, const char *fmt, va_list *va)
{
    int ret;
    size_t free_bytes = _free_bytes(self);
    if ((self->foot == 0) || (self->foot > self->head)) {
        /* In this case no wrap around of the ring buffer is possible and the
         * guarding byte can be used as the terminating null byte. */
        ret = vsnprintf(self->sbuf.data + self->head, free_bytes + 1, fmt, *va);
        self->head += ret;
    } else {
        /* Here a wrap around of the ring buffer can happen, since the lenght of
         * the formatted string is not known, a first attempt is done to write
         * the string to the ring buffer. */
        va_list orig_va;
        size_t chunk_size = self->sbuf.size - self->head;
        // Make a copy of the original va (variable arguments) pointer
        va_copy(orig_va, *va);
        // First, try to write it directly to the buffer, it may fit.
        ret = vsnprintf(self->sbuf.data + self->head, chunk_size, fmt, *va);
        if (ret > chunk_size) {
            // Unfortunately, the resulting formated string did not fit.
            char *tmp_buf;
            size_t tmp_buf_size = ret;
            // Limit the temporary buffer size to the free bytes in the buffer.
            if (tmp_buf_size > free_bytes) {
                tmp_buf_size = free_bytes;
            }
            // Allocate a temporary buffer to create the formatted string.
            tmp_buf = MALLOC(tmp_buf_size + 1);
            if (tmp_buf != NULL) {
                vsnprintf(tmp_buf, tmp_buf_size + 1, fmt, orig_va);
                // Write formatted string to ring buffer
                ret = write(self, tmp_buf, tmp_buf_size);
                FREE(tmp_buf);
            } else {
                ret = -1;
            }
        } else {
            // Yes, it fitted, calculate the new head pointer.
            self->head += ret;
        }
    }
    return ret;
}

bool rbuffer_discard(rbuffer *self)
{
    self->foot = self->head;
    return true;
}

