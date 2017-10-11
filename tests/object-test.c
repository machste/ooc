#include <object.h>
#include <util/log.h>

int main(int argc, char *argv[])
{
    object o;
    Log_info(" Object Test\n-------------\n");
    // Initialise object
    init(&o, Object, Object);
    // Test print method
    Log_info("* Test print()\n");
    print(&o);
    // Destroy object
    destroy(&o);
    return 0;
}
