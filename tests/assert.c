#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "assert.h"

void _test_ok()
{
	printf(".");
}

void _test_fail()
{
	fprintf(stderr, "TEST FAILED\n");
	exit(1);
}

int _expect_streq(const char *actual, const char *expected)
{
	if(!strcmp(actual, expected))
	{
		_test_ok();
		return 0;
	}
	fprintf(stderr, "expected: \"%s\"\n", expected);
	fprintf(stderr, "     got: \"%s\"\n", actual);
	_test_fail();
	return 1;
}

int _expect_eq(int actual, int expected)
{
	if(actual == expected)
	{
		_test_ok();
		return 0;
	}
	fprintf(stderr, "expected: %d\n", expected);
	fprintf(stderr, "     got: %d\n", actual);
	_test_fail();
	return 1;
}

int __float_close(float a, float b, float max_diff)
{
    float diff = fabs(a - b);
    a = fabs(a);
    b = fabs(b);
    float largest = (b > a) ? b : a;

    if (diff <= largest * max_diff)
        return 0;
    return 1;
}

int _expect_float_eq(float actual, float expected)
{
	if(!__float_close(actual, expected, 0.00012))
	{
		_test_ok();
		return 0;
	}
	fprintf(stderr, "expected: %f\n", expected);
	fprintf(stderr, "     got: %f\n", actual);
	_test_fail();
	return 1;
}

