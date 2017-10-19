#include <string.h>

#include <util/log.h>
#include <util/print.h>
#include <util/memory.h>
#include <util/rbuffer.h>

#define SOME_STUFF "<some stuff>"
#define RING_TEST_SEQUENCE "abc"

static void log_buffer(rbuffer *rbuf)
{
    rbuffer_fill_empty(rbuf, 'X');
    Log_debug("rbuffer: '%.*s', size: %zu, head: %zu, foot: %zu\n",
            rbuf->sbuf.size, rbuf->sbuf.data, rbuf->sbuf.size, rbuf->head,
            rbuf->foot);
}

static bool ring_test(rbuffer *rbuf)
{
    static const char *test_seq = RING_TEST_SEQUENCE;
    size_t test_seq_len = strlen(test_seq);
    char read_buffer[test_seq_len];
    for (int seq_len = 1; seq_len <= test_seq_len; seq_len++) {
        Log_info("Test with sequence: '%.*s'\n", seq_len, test_seq);
        for (int i = 0; i < 2 * rbuf->sbuf.size / seq_len; i++) {
            write(rbuf, test_seq, seq_len);
            log_buffer(rbuf);
            size_t read_size = read(rbuf, read_buffer, sizeof(read_buffer));
            if (read_size != seq_len) {
                Log_error("Expected read_size: %zu, got: %zu\n", seq_len,
                        read_size);
                return false;
            }
            if (memcmp(test_seq, read_buffer, seq_len) != 0) {
                Log_error("Expected string: '%.*s', got: '%.*s'\n",
                        seq_len, test_seq, seq_len, read_buffer);
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    char buffer[16];
    char read_buffer[6];
    int indexes[] = { 3, -1, -20 };
    char abc[] = { 'a', 'b', 'c' };
    rbuffer rbuf;
    Log_info(" Ring Buffer (RBuffer) Test\n----------------------------\n");
    /* Initialise rbuffer object */
    Log_info("\n* Test init()\n");
    init(&rbuf, RBuffer, buffer, sizeof(buffer));
    // Fill static buffer of ring buffer with 'X'
    log_buffer(&rbuf);
    /* Test print method */
    Log_info("\n* Test print()\n");
    print(&rbuf);
    // Test len() method
    Log_info("\n* Test len()\n");
    Log_info("rbuffer: len(): %zu\n", len(&rbuf));
    /* Test write method */
    Log_info("\n* Test write()\n");
    for (int i = 0; i < 2; i++) {
        size_t wrote_size = write(&rbuf, SOME_STUFF, strlen(SOME_STUFF));
        Log_info("wrote%i: '%.*s', size: %zu\n", i + 1, wrote_size, SOME_STUFF,
                wrote_size);
        log_buffer(&rbuf);
    }
    /* Test read method */
    Log_info("\n* Test read()\n");
    for (int i = 0; i < 2; i++) {
        size_t read_size = read(&rbuf, read_buffer, sizeof(read_buffer));
        Log_info("read%i: '%.*s', size: %zu\n", i + 1, read_size, read_buffer,
                read_size);
        log_buffer(&rbuf);
    }
    /* Test write over the end */
    Log_info("\n* Test writing over the end\n");
    write(&rbuf, SOME_STUFF, strlen(SOME_STUFF));
    log_buffer(&rbuf);
    /* Test len() method */
    Log_info("\n* Test len()\n");
    Log_info("rbuffer: len(): %zu\n", len(&rbuf));
    /* Test get_at() method */
    Log_info("\n* Test get_at()\n");
    for (int i = 0; i < ARRAY_SIZE(indexes); i++) {
        char *read_byte = get_at(&rbuf, indexes[i]);
        if (read_byte != NULL) {
            Log_info("rbuffer: get_at(%i): %c\n", indexes[i], *read_byte);
        } else {
            Log_info("fbuffer: get_at(%i): NULL\n", indexes[i]);
        }
    }
    /* Test set_at() method */
    Log_info("\n* Test set_at()\n");
    for (int i = 0; i < ARRAY_SIZE(indexes); i++) {
        int idx = indexes[i];
        char *byte = abc + i;
        char *set_byte = set_at(&rbuf, idx, byte);
        if (set_byte != NULL) {
            Log_info("rbuffer: set_at(%i, '%c'): %c\n", idx, *byte, *set_byte);
        } else {
            Log_info("rbuffer: set_at(%i, '%c'): NULL\n", idx, abc[i]);
        }
        log_buffer(&rbuf);
    }
    /* Test discard() method */
    Log_info("\n* Test discard()\n");
    discard(&rbuf);
    log_buffer(&rbuf);
    /* Test format() method */
    Log_info("\n* Test format(\"%%s %%s!\", \"Hello\", \"World\")\n");
    format(&rbuf, "%s %s!", "Hello", "World");
    log_buffer(&rbuf);
    /* Test clear() method */
    Log_info("\n* Test clear()\n");
    clear(&rbuf);
    log_buffer(&rbuf);
    /* Test ring functionality */
    Log_info("\n* Test ring functionality\n");
    if (ring_test(&rbuf)) {
        Log_info("Ring test: OK!\n");
    } else {
        Log_error("Ring test: FAILED!\n");
    }
    /* Destroy rbuffer object */
    destroy(&rbuf);
    return 0;
}
