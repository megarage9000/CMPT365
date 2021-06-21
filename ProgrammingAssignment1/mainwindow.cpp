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
    clearOutput();
    int minRgb = getMinRgbValues();
    bool invalidValues = false;
    if(minRgb < 0 || minRgb >= 255) {
        appendOutput("ERROR: Invalid minimum RGB values\n");
        invalidValues = true;
    }

    int maxRgb = getMaxRgbValues();
    if(maxRgb < 0 || maxRgb > 255 || minRgb >= maxRgb) {
        appendOutput("ERROR: Invalid maximum RGB values\n");
        invalidValues = true;
    }

    if(invalidValues){
        return;
    }
    else{
        MatrixLift::matrixOperation multiplication = MatrixLift::YCoCgMultiplication;
        MatrixLift::matrixOperation lifting = MatrixLift::YCoCgLifting;

        MatrixThread *multiplicationThread = new MatrixThread(this, minRgb, maxRgb, multiplication);
        connect(multiplicationThread, &MatrixThread::resultReady, this, &MainWindow::appendMultplicationOutput);
        connect(multiplicationThread, &MatrixThread::finished, multiplicationThread, &QObject::deleteLater);

        MatrixThread *liftingThread = new MatrixThread(this, minRgb, maxRgb, lifting);
        connect(liftingThread, &MatrixThread::resultReady, this, &MainWindow::appendLiftingOutput);
        connect(liftingThread, &MatrixThread::finished, liftingThread, &QObject::deleteLater);

        liftingThread->start();
        multiplicationThread->start();
    }
}



int MainWindow::getMinRgbValues(){
    return ui->MinRgbInput->text().toInt();
}

int MainWindow::getMaxRgbValues(){
    return ui->MaxRgbInput->text().toInt();
}

void MainWindow::setMultiplicationOutput(QString output){
    ui->matrixMultiplicationOutput->setPlainText(output);
}
void MainWindow::setLiftingOutput(QString output){
    ui->matrixLiftingOutput->setPlainText(output);
}

void MainWindow::appendMultplicationOutput(QString output){
    ui->matrixMultiplicationOutput->appendPlainText(output);
}
void MainWindow::appendLiftingOutput(QString output){
    ui->matrixLiftingOutput->appendPlainText(output);
}

void MainWindow::appendOutput(QString output) {
    appendLiftingOutput(output);
    appendMultplicationOutput(output);
}
void MainWindow::setOutput(QString output){
    setLiftingOutput(output);
    setMultiplicationOutput(output);
}

void MainWindow::clearOutput(){
    setOutput("");
}

void MainWindow::on_pushButtonCustom_clicked()
{
    clearOutput();
    int temp;
    double redValue = ((temp = ui->RedInput->text().toInt()) <= 255) ? temp : 0;
    double blueValue = ((temp = ui->BlueInput->text().toInt()) <= 255) ? temp : 0;
    double greenValue = ((temp = ui->GreenInput->text().toInt()) <= 255) ? temp : 0;

    double liftResult[3], multiplyResult[3];
    double input[3] = {greenValue, blueValue, redValue};
    MatrixLift::YCoCgLifting(input, liftResult, 3, 3);
    MatrixLift::YCoCgMultiplication(input, multiplyResult, 3, 3);

    setLiftingOutput(
                QString("- Cg = %1 \n- Y = %2 \n- Co = %3\n")
                .arg(liftResult[0]).arg(liftResult[1]).arg(liftResult[2])
                );
    setMultiplicationOutput(
                QString("- Cg = %1 \n- Y = %2 \n- Co = %3\n")
                .arg(multiplyResult[0]).arg(multiplyResult[1]).arg(multiplyResult[2])
                );
}

