#ifndef DTEST_H
#define DTEST_H

#include <stdio.h>
#include <setjmp.h>

/* In case there are still trolls who shun C99 */
#ifndef DISABLE_STDBOOL
#include <stdbool.h>
#else
typedef enum {false = 0, true = !false} bool;
#endif

/* Function Pointer typedef */
typedef void (*testFunc_p)(void);

/* Forward function declarations. I reccomend you use the macros just below instead. */
void InitializeTesting (const char* filename);
int EndTesting (void);

void RunTest(testFunc_p Func, const char *func_name, const int func_line_num);
void FailTest(const char *msg, const int line_num);

/* *******************************************************************
 *  dTest Suite Functions
 *  Make sure to use START_TESTING() before you try to RUN_TEST
 *  The function you pass to RUN_TEST should contain your ASSERTS.
 *  Ex: 
 *      void TestAssertFunction(void)
 *       {
 *           ASSERT(1 == 1)
 *       }
 *       int main(void)
 *       {
 *           START_TESTING();
 *           RUN_TEST(TestAssertFunction);
 *           return END_TESTING();
 *       }
 *  Try to use the macros below, they pass in more information and are 
 *  more succinct.
 *********************************************************************/

#define START_TESTING() InitializeTesting(__FILE__)
#define END_TESTING() EndTesting()
#define RUN_TEST(func) RunTest((func), (#func), __LINE__)

/* Forward Test Function Declarations */
void TestAssertEqualInt(int expected, int result, const char *str, int line_num);
/***********************
 *  dTest ASSERT Macros *
 ***********************/

/* Simple Boolean */
#define ASSERT_MSG(condition, msg)                 \
    if((condition) != true) FailTest(msg, __LINE__)
#define ASSERT_IS_FALSE_MSG(condition, msg)        \
    if((condition) != false) FailTest(msg, __LINE__)
#define ASSERT_IS_NULL_MSG(p, msg)                    \
    ASSERT_MSG(((p) == NULL), msg)
#define ASSERT_NOT_NULL_MSG(p, msg)                \
    ASSERT_MSG(((p) != NULL), msg)

#define ASSERT(condition)                          \
    ASSERT_MSG((condition), "Expression evaluated to FALSE")
#define ASSERT_IS_FALSE(condition)                 \
    ASSERT_IS_FALSE_MSG((condition), "Expression evaluated to TRUE")
#define ASSERT_IS_NULL(p)                             \
    ASSERT_IS_NULL_MSG((p), "Pointer is not NULL")
#define ASSERT_NOT_NULL(p)                         \
    ASSERT_NOT_NULL_MSG((p), "Pointer is NULL")

/* Comparisons */
#define ASSERT_EQUAL_INT_MSG(expected, result, msg) \
    TestAssertEqualInt((expected), (result), (msg), __LINE__)
#define ASSERT_EQUAL_INT(expected, result)          \
    TestAssertEqualInt((expected), (result), NULL, __LINE__)
#endif
