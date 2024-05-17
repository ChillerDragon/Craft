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

	a = 22.0f;
	b = 300.0f;
	c = 1.0f;

	normalize(&a, &b, &c);

	EXPECT_FLOAT_EQ(a, 0.073137f);
	EXPECT_FLOAT_EQ(b, 0.997316f);
	EXPECT_FLOAT_EQ(c, 0.003324f);
}

