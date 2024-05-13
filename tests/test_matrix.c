#include "matrix.h"

#include "assert.h"

int main() {
	float a = 1.0f;
	float b = 1.0f;
	float c = 1.0f;

	normalize(&a, &b, &c);

	EXPECT_FLOAT_EQ(a, 0.577350f);
	EXPECT_FLOAT_EQ(b, 0.577350f);
	EXPECT_FLOAT_EQ(c, 0.577350f);
}

