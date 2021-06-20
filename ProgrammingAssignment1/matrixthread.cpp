#include "matrixthread.h"

MatrixThread::MatrixThread(QObject *parent,
                           int min,
                           int max,
                           MatrixLift::matrixOperation &operation)
: QThread(parent) {
    minValue = min;
    maxValue = max;
    this->operation = operation;
}

void MatrixThread::run() {

    int gbr[3] = {0, 0, 0};

    for(int g = minValue; g <= maxValue; g++){
        gbr[0] = g;
        for(int b = minValue; b <= maxValue; b++){
            gbr[1] = b;
            for(int r = minValue; r <= maxValue; r++){
                gbr[2] = r;
                int cgyco[3] = {0, 0, 0};
                operation(gbr, cgyco, 3, 3);
                QString result = QString(
                    "G = %1, B = %2, R = %3 \n"
                    "Cg = %4, Y = %5, Co = %6\n"
                    " ----- \n")
                    .arg(gbr[0]).arg(gbr[1]).arg(gbr[2]).arg(cgyco[0]).arg(cgyco[1]).arg(cgyco[2]);
                emit resultReady(result);
            }
        }
    }
}
