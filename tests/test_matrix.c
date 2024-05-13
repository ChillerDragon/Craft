#include <stdio.h>

#include "world.h"
#include "matrix.h"

int main() {


	// create_world(10, 10, NULL, NULL);
	puts("hello world");

	float a = 1.0f;
	float b = 1.0f;
	float c = 1.0f;

	normalize(&a, &b, &c);

	printf("%f\n", a);

}
