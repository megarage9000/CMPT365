#ifndef DCTTRANSFORM_H
#define DCTTRANSFORM_H


#include <iostream>
#include <vector>
#include <math.h>

const int DIMENSION = 8;
const double EMPTY_VALUE = 0;

class dctTransform
{
public:
    dctTransform(std::vector<std::vector<int>> values);

private:
    double getDctTransform(int i, int j, int n);
    std::vector<std::vector<double>> getTranspose(std::vector<std::vector<double>> inputMatrix);

    std::vector<std::vector<double>> transform;
    std::vector<std::vector<double>> transformTranspose;
};

std::vector<std::vector<double>> createSubMatrix(std::vector<std::vector<int>> values, int rowStart, int colStart, int rowEnd, int colEnd);


#endif // DCTTRANSFORM_H
