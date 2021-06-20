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
    if(minRgb < 0 || minRgb >= 255) {
        appendOutput("ERROR: Invalid minimum RGB values\n");
    }

    int maxRgb = getMaxRgbValues();
    if(maxRgb < 0 || maxRgb > 255 || minRgb >= maxRgb) {
        appendOutput("ERROR: Invalid maximum RGB values\n");
    }
}

int MainWindow::getMinRgbValues(){
    return ui->MinRgbInput->text().toInt();
}

int MainWindow::getMaxRgbValues(){
    return ui->MaxRgbInput->text().toInt();
}

void MainWindow::setMultplicationOutput(QString output){
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
    setMultplicationOutput(output);
}

void MainWindow::clearOutput(){
    setOutput("");
}



