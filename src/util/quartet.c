#include <ctype.h>

#include <util/quartet.h>

bool quartet_valid(quartet_t quartet)
{
    return quartet <= QUARTET_MAX;
}

hexdigit_t quartet_hexdigit(quartet_t quartet)
{
    quartet = QUARTET_LO(quartet);
    return (quartet > 9) ? 'a' + (quartet - 10) : '0' + quartet;
}

quartet_t hexdigit_to_quartet(hexdigit_t hexdigit)
{
    int c = tolower(hexdigit);
    if(c < '0') {
        return -1;
    } else if (c <= '9') {
        return c - '0';
    } else if (c < 'a') {
        return -1;
    } else if (c <= 'f') {
        return c - 'a' + 10;
    } else {
        return -1;
    }
}
