#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cobsm.h"

// #define CTEST_ENABLED
#include "ctest.h"

#define debug_print(fmt, ...)                                                                                          \
    do {                                                                                                               \
        if (DEBUG)                                                                                                     \
            fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__);                            \
    } while (0)

void ctest_callback(const char *name, int line) {
    if (line < 0) {
        printf("CTEST : fail in %s line %d\n", name, -line);
    } else {
        printf("CTEST : pass in %s line %d\n", name, line);
    }
}

static uint8_t bin2hex(uint8_t bin) {
    bin &= 0x0F;
    if (bin < 10) {
        return bin + '0';
    } else {
        return bin + 'A' - 10;
    }
}

static uint8_t puthex(uint8_t bin) {
    putchar(bin2hex(bin >> 4));
    putchar(bin2hex(bin));
}

void hexdump(const uint8_t buffer[], uint8_t size) {
    uint8_t index = 0;
    puthex(size);
    while (index < size) {
        if (index & 0x0F) {
            putchar(' ');
        } else {
            if (index) {
                putchar('\n');
            }
            putchar('\t');
        }
        puthex(bin2hex(buffer[index++]));
    }
    putchar('\n');
}

struct tests {
    const uint8_t *test_vector;
    const uint8_t test_size;
};

static const uint8_t test_0[] = {0, 0, 0, 0};
static const uint8_t test_1[] = {'1', '2', '3', '4', '5'};
static const uint8_t test_2[] = {'1', '2', '3', '4', '5', 0};
static const uint8_t test_3[] = {'1', '2', '3', '4', '5', 0, '7', '8', '9'};
static const uint8_t test_4[] = {'1', '2', '3', '4', '5', 0, '6', '7', '8', '9', 0};
static const uint8_t test_5[] = {2, '3', '4', '5', 0, '6', '7', '8', '9', 0};
static const uint8_t test_6[] = {1, 2, 3, 4};
static const uint8_t test_7[] = {4, 2, 3, 4, 0};
static const uint8_t test_8[] = {7, 0, 3, 0, 0, 5};
static const uint8_t test_9[] = {3, 2, 0, 3, 4, 0, 5, 6, 7};

struct tests test_list[] = {
    {test_0, sizeof(test_0)}, {test_1, sizeof(test_1)}, {test_2, sizeof(test_2)}, {test_3, sizeof(test_3)},
    {test_4, sizeof(test_4)}, {test_5, sizeof(test_5)}, {test_6, sizeof(test_6)}, {test_7, sizeof(test_7)},
    {test_8, sizeof(test_8)}, {test_9, sizeof(test_9)},
};

uint8_t test_count = sizeof(test_list) / sizeof(struct tests);

bool test_codec(const uint8_t buffer[], uint8_t size) {
    uint8_t test_buffer[256] = {0};
    memcpy(test_buffer, buffer, size);
    hexdump(buffer, size);
    uint8_t test_size = cobsm_encode(test_buffer, size);
    hexdump(test_buffer, test_size);
    uint8_t decoded_size = cobsm_decode(test_buffer, test_size);
    hexdump(test_buffer, decoded_size);
    return (memcmp(test_buffer, buffer, size) == 0) && (decoded_size = size);
}

CTEST_FUNCTION(test) {
    CTEST_ASSERT(test_codec(test_0, sizeof(test_0)));
    CTEST_ASSERT(test_codec(test_1, sizeof(test_1)));
    CTEST_ASSERT(test_codec(test_2, sizeof(test_2)));
    CTEST_ASSERT(test_codec(test_3, sizeof(test_3)));
    CTEST_ASSERT(test_codec(test_4, sizeof(test_4)));
    CTEST_ASSERT(test_codec(test_5, sizeof(test_5)));
    CTEST_ASSERT(test_codec(test_6, sizeof(test_6)));
    CTEST_ASSERT(test_codec(test_7, sizeof(test_7)));
    CTEST_ASSERT(test_codec(test_8, sizeof(test_8)));
    CTEST_ASSERT(test_codec(test_9, sizeof(test_9)));
}

int main() {
    CTEST_RUN(test);

    return EXIT_SUCCESS;
}