#include <util/log.h>
#include <util/octet.h>

int main(int argc, char *argv[])
{
    octet_t octets[] = { 0xde, 0xad, 0xbe, 0xef, 0x12, 0x34 };
    char data[18];
    size_t bytes;
    hexduet_t hexduet;
    octet_t octet;
    bool ok;
    Log_info(" Octet Test\n-------------\n");
    hexduet = octet_to_hexduet(0x1a);
    Log_info("octet_to_hexduet(0x1a): %.*s\n", sizeof(hexduet), &hexduet);
    bytes = octet_to_cstr(0x2b, data, sizeof(data));
    Log_info("octet_to_cstr(0x2b, data, sizeof(data)): %zu\n", bytes);
    Log_info("data: %s\n", data);
    ok = hexduet_to_octet((hexduet_t){ 'a', 'b' }, &octet);
    Log_info("hexduet_to_octet((hexduet_t){ 'a', 'b' }, &octet): %i\n", ok);
    Log_info("octet: %02x\n", octet);
    bytes = octets_to_cstr(octets, sizeof(octets), data, sizeof(data), ':');
    Log_info("octets_to_cstr(octets, sizeof(octets), data, "
            "sizeof(data), ':' ): %zu\n", bytes);
    Log_info("data: %s\n", data);
    return 0;
}
