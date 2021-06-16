#ifndef MATRIXLIFT_H
#define MATRIXLIFT_H

#include <array>



namespace MatrixLift {
    using namespace std;
    constexpr float YCoCgMatrix[3][3] = {
        {0.5f, -0.25f, -0.25f},
        {0.5f, 0.25f, 0.25f},
        {0.0f, -0.5f, 0.5f}
    };
    void YCoCgMuliplication(float rgbVals[], float result[], int sizeRgb, int sizeResult);
    void YCoCgLifitng(float rgbVals[], float result[], int sizeRgb, int sizeResult);
}


#endif // MATRIXLIFT_H
