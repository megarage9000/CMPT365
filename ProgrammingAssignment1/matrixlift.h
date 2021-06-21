#ifndef MATRIXLIFT_H
#define MATRIXLIFT_H
namespace MatrixLift {

    void YCoCgMultiplication(double rgbVals[], double result[], int sizeRgb, int sizeResult);
    void YCoCgLifting(double rgbVals[], double result[], int sizeRgb, int sizeResult);
    typedef void(*matrixOperation)(double[], double[], int, int) ;
}


#endif // MATRIXLIFT_H
