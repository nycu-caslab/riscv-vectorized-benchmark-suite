#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

extern int32_t vmv_x_s_8(int32_t *data_addr);
extern int32_t vmv_x_s_16(int32_t *data_addr);
extern int32_t vmv_x_s_32(int32_t *data_addr);

struct test_case {
    int32_t  test[4];
    int32_t  expected;
};

bool test_vmv_x_s_8(void)
{
    int32_t value = 0;

    struct test_case vmv_x_s_8_tests[3] = {
        {.test = {0x323b3ff5, 0x47434b3a, 0x302f2e32, 0xe8404a51}, .expected = 0xfffffff5},
        {.test = {0x3f44383b, 0x37424d54, 0x5e4b5049, 0x4c4c4c4a}, .expected = 0x3b},
        {.test = {0x3a3e3738, 0x312f2e2f, 0x46424949, 0x49413c38}, .expected = 0x38},
    };

    for (uint32_t index = 0; index < 3; ++index)
    {
        value = vmv_x_s_8(vmv_x_s_8_tests[index].test);

        if (vmv_x_s_8_tests[index].test[0] != vmv_x_s_8_tests[index].expected)
        {
            printf("[case %d] The expected value is 0x%x but got 0x%x \n" , index,
                vmv_x_s_8_tests[index].expected, vmv_x_s_8_tests[index].test[0]);
            return false;
        }
    }
    return true;
}

bool test_vmv_x_s_16(void)
{
    int32_t value = 0;

    struct test_case vmv_x_s_16_tests[3] = {
        {.test = {0x323b3ff5, 0x47434b3a, 0x302f2e32, 0xe8404a51}, .expected = 0x3ff5},
        {.test = {0x3f44383b, 0x37424d54, 0x5e4b5049, 0x4c4c4c4a}, .expected = 0x383b},
        {.test = {0x3a3ef738, 0x312f2e2f, 0x46424949, 0x49413c38}, .expected = 0xfffff738},
    };

    for (uint32_t index = 0; index < 3; ++index)
    {
        value = vmv_x_s_16(vmv_x_s_16_tests[index].test);

        if (vmv_x_s_16_tests[index].test[0] != vmv_x_s_16_tests[index].expected)
        {
            printf("[case %d] The expected value is 0x%x but got 0x%x \n" , index,
                vmv_x_s_16_tests[index].expected, vmv_x_s_16_tests[index].test[0]);
            return false;
        }
    }
    return true;
}


bool test_vmv_x_s_32(void)
{
    int32_t value = 0;

    struct test_case vmv_x_s_32_tests[3] = {
        {.test = {0x323b3ff5, 0x47434b3a, 0x302f2e32, 0xe8404a51}, .expected = 0x323b3ff5},
        {.test = {0x3f44383b, 0x37424d54, 0x5e4b5049, 0x4c4c4c4a}, .expected = 0x3f44383b},
        {.test = {0x3a3e3738, 0x312f2e2f, 0x46424949, 0x49413c38}, .expected = 0x3a3e3738},
    };

    for (uint32_t index = 0; index < 3; ++index)
    {
        value = vmv_x_s_32(vmv_x_s_32_tests[index].test);

        if (vmv_x_s_32_tests[index].test[0] != vmv_x_s_32_tests[index].expected)
        {
            printf("[case %d] The expected value is 0x%x but got 0x%x \n" , index,
                vmv_x_s_32_tests[index].expected, vmv_x_s_32_tests[index].test[0]);
            return false;
        }
    }
    return true;
}

struct test_suite {
    char *name;
    bool(*test_func)();
};

struct test_suite vmv_x_s[3] = {
    {.name = "Test_vmv_x_s_8", .test_func = &test_vmv_x_s_8},
    {.name = "Test_vmv_x_s_16", .test_func = &test_vmv_x_s_16},
    {.name = "Test_vmv_x_s_32", .test_func = &test_vmv_x_s_32},
};

int main(void)
{
    bool result;
    uint32_t cases = sizeof(vmv_x_s) / sizeof(struct test_suite);
    for (uint32_t index = 0; index < cases; ++index)
    {
        printf("%s : \n", vmv_x_s[index].name);
        result = vmv_x_s[index].test_func();

        printf("%s \n", result ? "PASS" : "FAILED");
    }

    return 0;
}