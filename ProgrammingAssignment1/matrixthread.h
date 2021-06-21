#ifndef MATRIXTHREAD_H
#define MATRIXTHREAD_H

#include <QThread>
#include <chrono>
#include "matrixlift.h"

class MatrixThread : public QThread{
    Q_OBJECT
public:
    MatrixThread(QObject *parent, int min, int max, MatrixLift::matrixOperation &operation);

    void run() override;
signals:
    void resultReady(const QString &result);

private:
    int minValue;
    int maxValue;
    MatrixLift::matrixOperation  operation;
};

#endif // MATRIXTHREAD_H
