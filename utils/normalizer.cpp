#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "normalizer.h"

using namespace std;

Normalizer ::Normalizer() {}

void Normalizer ::normalize(float *v)
{
	float N = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

	for (int i = 0; i < 3; i++)
	{
		v[i] = v[i] / N;
	}
}

float *Normalizer ::crossProduct(float *a, float *b)
{
	float result[] = {
			a[1] * b[2] - a[2] * b[1], // X
			a[0] * b[2] - a[2] * b[0], // y
			a[0] * b[1] - a[1] * b[0]};// z

	for (int i = 0; i < 3; i++)
	{
		cout << "\n" << result[i];
	}

	cout << "\n\nAfter Normalize\n";

	this->normalize(result);

	for (int i = 0; i < 3; i++)
	{
		cout << "\n" << result[i];
	}

	return result;
}

float *Normalizer ::calculateNormal(float *a, float *b, float *c)
{
	float X[] = {
			b[0] - a[0],
			b[1] - a[1],
			b[2] - a[2]};

	float Y[] = {
			c[0] - a[0],
			c[1] - a[1],
			c[2] - a[2]};

	float *result = this->crossProduct(X, Y);

	return result;
}