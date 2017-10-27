#include <util/print.h>
#include <util/log.h>
#include <object.h>


int main(int argc, char *argv[])
{
    object o;
    Log_info(" Object Test\n-------------\n");
    // Initialise object
    init(&o, Object, Object);
    // Test print method
    Log_info("\n* Test print()\n");
    print("Hello %s, i: %i%%, obj: %O, &obj: %p", "World", 99, &o, &o);
    // Destroy object
    destroy(&o);
    return 0;
}
