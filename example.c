#include "dTest.h"

void TestTheTests(void)
{
    ASSERT(1 == 1);
    ASSERT_IS_FALSE_MSG((3 + 5) == 6, "Basic Math Failed!");
    void *p = NULL;
    ASSERT_IS_NULL(p);
}

void TestEqualInt(void)
{
    ASSERT_EQUAL_INT(10, 10);
    ASSERT_EQUAL_INT_MSG(1, 0, "Wow! This number isn't the same at all!");
}

int main(void)
{
    START_TESTING();
    RUN_TEST(TestTheTests);
    RUN_TEST(TestEqualInt);
    int fails = END_TESTING();
    return fails;
}
