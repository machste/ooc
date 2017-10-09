#include <string.h>

#include <util/log.h>
#include <util/print.h>
#include <util/memory.h>
#include <util/sbuffer.h>


int main(int argc, char *argv[])
{
    int indexes[] = { 3, 17, -1 };
    char abc[] = { 'a', 'b', 'c' };
    char data[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    sbuffer sbuf;
    Log_info(" Static Buffer (SBuffer) Test\n------------------------------\n");
    /* Initialise sbuffer object */
    init(&sbuf, SBuffer, data, sizeof(data));
    /* Test print() method */
    Log_info("\n* Test print()\n");
    print(&sbuf);
    /* Test len() method */
    Log_info("\n* Test len()\n");
    Log_info("sbuffer: lenght: %zu\n", len(&sbuf));
    /* Test get_at() method */
    Log_info("\n* Test get_at()\n");
    Log_info("sbuffer: data: %.*s\n", sbuf.size, sbuf.data);
    for (int i = 0; i < ARRAY_SIZE(indexes); i++) {
        char *read_byte = get_at(&sbuf, indexes[i]);
        if (read_byte != NULL) {
            Log_info("sbuffer: get_at(%i): %c\n", indexes[i], *read_byte);
        } else {
            Log_info("sbuffer: get_at(%i): NULL\n", indexes[i]);
        }
    }
    /* Test set_at() method */
    Log_info("\n* Test set_at()\n");
    for (int i = 0; i < ARRAY_SIZE(indexes); i++) {
        int idx = indexes[i];
        char *byte = abc + i;
        char *set_byte = set_at(&sbuf, idx, byte);
        if (set_byte != NULL) {
            Log_info("sbuffer: set_at(%i, '%c'): %c\n", idx, *byte, *set_byte);
        } else {
            Log_info("sbuffer: set_at(%i, '%c'): NULL\n", idx, abc[i]);
        }
        Log_info("sbuffer: data: %.*s\n", sbuf.size, sbuf.data);
    }
    /* Destroy sbuffer object */
    destroy(&sbuf);
    return 0;
}
