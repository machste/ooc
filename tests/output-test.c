#include <output.h>
#include <util/log.h>

const char data[] = "some data";

int main(int argc, char *argv[])
{
    output out;
    Log_info(" Output Test\n-------------\n");
    // Initialise output object
    init(&out, &Output);
    // Test print method
    Log_info("* Test print()\n");
    print(&out);
    // Test write method
    Log_info("* Test write()\n");
    write(&out, data, sizeof(data));
    write(&out, "\n", 1);
    // Test format method
    Log_info("* Test format()\n");
    format(&out, "Data: %s\n", data);
    // Destroy output object
    destroy(&out);
    return 0;
}
