#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->matrixLiftingOutput->setReadOnly(true);
    ui->matrixMultiplicationOutput->setReadOnly(true);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Execute(){

}

void MainWindow::on_pushButton_clicked()
{

//    textThreadLifting = new TextThread(this);
//    connect(textThreadLifting, SIGNAL(signalOutput(const QString&)), this, SLOT(appendMatrixLiftingOutput(const QString&)));
//    connect(textThreadLifting, SIGNAL(finished()), textThreadLifting, SLOT(deleteLater()));
//    textThreadMultiplication = new TextThread(this);
//    connect(textThreadMultiplication, SIGNAL(signalOutput(const QString&)), this, SLOT(appendMatrixMultiplicationOutput(const QString&)));
//    connect(textThreadMultiplication, SIGNAL(finished()), textThreadMultiplication, SLOT(deleteLater()));

//    textThreadLifting->start();
//    textThreadMultiplication->start();

    ui->matrixLiftingOutput->setPlainText(QString("In calculation"));
    ui->matrixMultiplicationOutput->setPlainText(QString(""));

    QString outputLift = QString("-----/n Lifting results: /n-----/n");
    QString outputMultiplication = QString("-----/n Multiplication results: /n-----/n");
    int rgbVals[3] = {0, 0, 0};
    int results[3];

//    // Run matrix Multiplication
//    for(int g = 0; g < 256; g++){
//        rgbVals[0] = g;
//        for(int b = 0; b < 256; b++) {
//            rgbVals[1] = b;
//            for(int r = 0; r < 256; r++){
//                rgbVals[2] = r;
//                MatrixLift::YCoCgMuliplication(rgbVals, results, 3, 3);
//                QString output;
//                QTextStream(&output) << "YCgCo values :" <<
//                                        "\nCg = " << results[0] <<
//                                        "\nY = " << results[1] <<
//                                        "\nCo = " << results[2] <<
//                                        "\n----\n";
//                std::cout << output.toStdString();
//                outputMultiplication.append(output);
//            }
//        }
//    }
//    ui->matrixMultiplicationOutput->setPlainText(outputMultiplication);

    // Run matrix Multiplication

    rgbVals[0] = rgbVals[1] = rgbVals[2] = 0;
    for(int g = 0; g < 100; g++){
        rgbVals[0] = g;
        for(int b = 0; b < 100; b++) {
            rgbVals[1] = b;
            for(int r = 0; r < 100; r++){
                rgbVals[2] = r;
                MatrixLift::YCoCgLifitng(rgbVals, results, 3, 3);
                QString output = QString("RGB values: G = %1, B = %2, R = %3\n YCoCg values: Cg = %4, Y = %5, Co = %6 \n ----- \n")
                        .arg(rgbVals[0]).arg(rgbVals[1]).arg(rgbVals[2]).arg(results[0]).arg(results[1]).arg(results[2]);
                appendMatrixLiftingOutput(output);
                QCoreApplication::processEvents();
            }
        }
    }
}

void MainWindow::appendMatrixLiftingOutput(const QString &output) {
    ui->matrixLiftingOutput->appendPlainText(output);
}

void MainWindow::appendMatrixMultiplicationOutput(const QString &output) {
    ui->matrixLiftingOutput->appendPlainText(output);
}



