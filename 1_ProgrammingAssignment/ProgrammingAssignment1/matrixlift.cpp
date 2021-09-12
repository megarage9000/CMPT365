#include "matrixlift.h"

namespace MatrixLift {

    void YCoCgMultiplication(double rgbVals[], double result[], int sizeRgb, int sizeResult){
        if(sizeRgb != sizeResult){
            return;
        }

        int g = rgbVals[0];
        int b = rgbVals[1];
        int r = rgbVals[2];

        result[0] = (g >> 1) - (b >> 2) - (r >> 2); // Cg
        result[1] = (g >> 1) + (b >> 2) + (r >> 2); // Y
        result[2] = -(b >> 1) + (r >> 1);           // Co
    }

    void YCoCgLifting(double rgbVals[], double result[], int sizeRgb, int sizeResult){
        if(sizeRgb != sizeResult){
            return;
        }

        int g = rgbVals[0];
        int b = rgbVals[1];
        int r = rgbVals[2];

        result[2] = r - b; // Co
        int temp = b + ((r - b) >> 1);
        result[0] = g - temp; // Cg
        result[1] = temp + ((g - temp) >> 1); // Y

        result[0] = (int)result[0] >> 1; // Scaling down Cg
        result[2] = (int)result[2] >> 1; // Scaling down Co
    }
}
