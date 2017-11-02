#include <util/octet.h>
#include <util/rbuffer.h>

hexduet_t octet_to_hexduet(octet_t octet)
{
    hexduet_t digits;
    digits.high = quartet_hexdigit(QUARTET_HI(octet));
    digits.low = quartet_hexdigit(QUARTET_LO(octet));
    return digits;
}

int octet_put(octet_t octet, output *out)
{
    hexduet_t digits = octet_to_hexduet(octet);
    return write(out, (char *)&digits, sizeof(hexduet_t));
}

size_t octet_to_cstr(octet_t octet, char *cstr, size_t size)
{
    size_t ret;
    rbuffer buf;
    init(&buf, RBuffer, cstr, size);
    ret = octet_put(octet, &buf.sbuf.base.out);
    cstr[ret] = '\0';
    destroy(&buf);
    return ret;
}

#define OCTETS_TO_PUT 8

int octets_put(octet_t *octets, size_t n, output *out, char sep)
{
    int ret = 0;
    size_t pos = 0;
    char cstr[(sizeof(hexduet_t) + 1) * OCTETS_TO_PUT];
    for (int i = 0; i < n; i++) {
        *(hexduet_t *)(cstr + pos) = octet_to_hexduet(octets[i]);
        pos += 2;
        // Put separator after each octet except after the last
        if (i < n - 1) {
            cstr[pos++] = sep;
        }
        // If the internal buffer (cstr) is full write it to the output
        if ((pos >= (sizeof(cstr) - 1)) || (i == n - 1)) {
            int len = write(out, cstr, pos);
            if (len > 0) {
                ret += len;
                pos = 0;
            } else {
                ret = -1;
                break;
            }
        }
    }
    return ret;
}

size_t octets_to_cstr(octet_t *octets, size_t n, char *cstr, size_t size,
        char sep)
{
    size_t ret;
    rbuffer buf;
    init(&buf, RBuffer, cstr, size);
    ret = octets_put(octets, n, &buf.sbuf.base.out, sep);
    cstr[ret] = '\0';
    destroy(&buf);
    return ret;
}

bool hexduet_to_octet(hexduet_t hexduet, octet_t *octet)
{
    int q_low = hexdigit_to_quartet(hexduet.low);
    if (quartet_valid(q_low)) {
        int q_high =  hexdigit_to_quartet(hexduet.high);
        if (quartet_valid(q_high)) {
            // Calculate value of octet
            *octet = q_low + 16 * q_high;
            return true;
        }
    }
    return false;
}
