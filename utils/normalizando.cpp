#include <stdio.h>

using namespace std;

#include "normalizer.h"

int main(int argc, char const *argv[])
{
    Normalizer NZ;
    float v[3][3] = {0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};
    NZ.calculateNormal(v[0],v[1],v[2]);
    return 0;
}
