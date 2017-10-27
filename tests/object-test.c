#include <util/assert.h>
#include <util/memory.h>
#include <util/print.h>
#include <util/log.h>
#include <object.h>


static void test_to_cstr(object *obj)
{
    char *cstr = NULL;
    size_t len = 0;
    Log_info("\n* Test to_cstr()\n");
    len = to_cstr(obj, cstr, 0);
    Log_info("Required C-string length: %zu\n", len);
    cstr = MALLOC(len + 1);
    ASSERT(cstr != NULL);
    len = to_cstr(obj, cstr, len + 1);
    Log_info("C-string: '%s', length: %zu\n", cstr, len);
}

int main(int argc, char *argv[])
{
    object o;
    Log_info(" Object Test\n-------------\n");
    // Initialise object
    init(&o, Object, Object);
    // Test print method
    Log_info("\n* Test print()\n");
    print("%o", &o);
    // Test to_cstr method
    test_to_cstr(&o);
    // Destroy object
    destroy(&o);
    return 0;
}
