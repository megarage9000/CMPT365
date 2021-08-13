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
    dctTransform(std::vector<std::vector<int>> values, bool inverse);
    std::vector<std::vector<int>> result;

private:
    double getDctTransform(int i, int j, int n);
    std::vector<std::vector<double>> getTranspose(std::vector<std::vector<double>> inputMatrix);

    std::vector<std::vector<double>> transform;
    std::vector<std::vector<double>> transformTranspose;

    int quantTable[8][8] = {
        {1, 1, 2, 4, 8, 16, 32, 64},
        {1, 1, 2, 4, 8, 16, 32, 64},
        {2, 2, 2, 4, 8, 16, 32, 64},
        {4, 4, 4, 4, 8, 16, 32, 64},
        {8, 8, 8, 8, 8, 16, 32, 64},
        {16, 16, 16, 16, 16, 16, 32, 64},
        {32, 32, 32, 32, 32, 32, 32, 64},
        {64, 64, 64, 64, 64, 64, 64, 64}
    };

};


std::vector<std::vector<double>> matrixMultiplication(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B);
std::vector<std::vector<double>> createSubMatrix(std::vector<std::vector<int>> values, int rowStart, int colStart, int rowEnd, int colEnd);
void mapMatrixValues(std::vector<std::vector<int>>* dest, std::vector<std::vector<double>> source, int rowStart, int colStart, int rowEnd, int colEnd);



#endif // DCTTRANSFORM_H
