#ifndef TESTS_ASSERT
#define TESTS_ASSERT

void _test_ok();
void _test_fail();
int _expect_streq(const char *actual, const char *expected);
int _expect_eq(int actual, int expected);
int _expect_float_eq(float actual, float expected);

#define EXPECT_STREQ(actual, expected) _expect_streq(actual, expected);
#define EXPECT_EQ(actual, expected) _expect_eq(actual, expected);
#define EXPECT_FLOAT_EQ(actual, expected) _expect_float_eq(actual, expected);

#endif

