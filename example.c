#include <assert.h>
#include "dTest.h"

void TestTheTests(void)
{
    ASSERT(1 == 1);
    ASSERT_IS_FALSE_MSG((3 + 5) == 6, "Basic Math Failed!");
    void *p = NULL;
    ASSERT_IS_NULL(p);
}

int main(void)
{
    START_TESTING();
    RUN_TEST(TestTheTests);
    int fails = END_TESTING();
    assert(fails == 0);
    return 0;
}
