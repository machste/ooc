#include <string.h>

#include <util/log.h>
#include <util/print.h>
#include <util/memory.h>
#include <util/sstr.h>


int main(int argc, char *argv[])
{
    int indexes[] = { 3, 11, -2 };
    char abc[] = { '1', '2', '3' };
    const char *text = "This is some funny test text.";
    char read_buffer[8];
    size_t n;
    char data[16];
    sstr s;
    Log_info(" Static String (SStr) Test\n---------------------------\n");
    /* Initialise sstr object */
    init(&s, SStr, data, sizeof(data), "Hallo %s!", "Welt");
    /* Test print() method */
    Log_info("\n* Test print()\n");
    print(&s);
    /* Test len() method */
    Log_info("\n* Test len()\n");
    Log_info("sstr: length: %zu\n", len(&s));
    // Test cstr() method */
    Log_info("\n* Test cstr()\n");
    Log_info("sstr: '%s'\n", cstr(&s));
    // Test get_at() method */
    Log_info("\n* Test get_at()\n");
    for (int i = 0; i < ARRAY_SIZE(indexes); i++) {
        int idx = indexes[i];
        char *ch = get_at(&s, idx);
        if (ch != NULL) {
            Log_info("sstr: get_at(%i): %c\n", idx, *ch);
        } else {
            Log_info("sstr: get_at(%i): NULL\n", idx);
        }
    }
    /* Test set_at() method */
    Log_info("\n* Test set_at()\n");
    for (int i = 0; i < ARRAY_SIZE(indexes); i++) {
        int idx = indexes[i];
        char *ch = abc + i;
        char *set_ch = set_at(&s, idx, ch);
        if (set_ch != NULL) {
            Log_info("sstr: set_at(%i, '%c'): %c\n", idx, *ch, *set_ch);
        } else {
            Log_info("sstr: set_at(%i, '%c'): NULL\n", idx, abc[i]);
        }
        Log_info("sstr: '%s'\n", cstr(&s));
    }
    /* Test clear() method */
    Log_info("\n* Test clear()\n");
    clear(&s);
    Log_info("sstr: '%s' (len: %zu)\n", cstr(&s), len(&s));
    /* Test write() method */
    Log_info("\n* Test write(\"%s\" , 3)\n", text);
    n = write(&s, text, 3);
    Log_info("sstr: '%s' (n: %zu)\n", cstr(&s), n);
    Log_info("\n* Test write(\"%s\" , strlen(text))\n", text);
    n = write(&s, text, strlen(text));
    Log_info("sstr: '%s' (n: %zu)\n", cstr(&s), n);
    /* Test format() method */
    Log_info("\n* Test format(\"%%s %%i!\", \"Hello\", 42)\n");
    format(&s, "%s %i!", "Hello", 42);
    Log_info("sstr: '%s'\n", cstr(&s));
    /* Test read() method */
    Log_info("\n* Test read(read_buffer, sizeof(read_buffer))\n");
    n = read(&s, read_buffer, sizeof(read_buffer));
    Log_info("read: '%.*s' (n: %zu)\n", n, read_buffer, n);
    Log_info("\n* Test read(read_buffer, 4)\n");
    n = read(&s, read_buffer, 4);
    Log_info("read: '%.*s' (n: %zu)\n", n, read_buffer, n);
    /* Destroy sstr object */
    destroy(&s);
    return 0;
}
