#include "dTest.h"

void TestTheTests(void)
{
    TEST_ASSERT(1 == 1);
    TEST_ASSERT_IS_FALSE_MSG((3 + 3) == 6, "Basic Math Worked!");
    void *p = NULL;
    TEST_ASSERT_NULL(p);
}

int main(void)
{
    START_TESTING();
    RUN_TEST(TestTheTests);
    return END_TESTING();
}
