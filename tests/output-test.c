#include <util/log.h>
#include <util/print.h>
#include <output.h>

const char data[] = "some data";

int main(int argc, char *argv[])
{
    output out;
    Log_info(" Output Test\n-------------\n");
    // Initialise output object
    init(&out, Output);
    // Test print method
    Log_info("\n* Test print()\n");
    print("%o", &out);
    // Test write method
    Log_info("\n* Test write()\n");
    write(&out, data, sizeof(data));
    write(&out, "\n", 1);
    // Test format method
    Log_info("\n* Test format()\n");
    format(&out, "Data: %s, %.3f\n", data, 3.14159265359);
    // Destroy output object
    destroy(&out);
    return 0;
}
