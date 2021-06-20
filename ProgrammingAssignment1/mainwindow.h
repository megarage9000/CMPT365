#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <iostream>
#include <string>
#include "matrixlift.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; class MatrixThread; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Execute();

private slots:
    void on_pushButton_clicked();
    int getMinRgbValues();
    int getMaxRgbValues();
    void setMultplicationOutput(QString output);
    void setLiftingOutput(QString output);
    void appendMultplicationOutput(QString output);
    void appendLiftingOutput(QString output);
    void appendOutput(QString output);
    void setOutput(QString output);
    void clearOutput();


private:
    Ui::MainWindow *ui;
    void runMultiplication();
    void runLifting();
};

class MatrixThread : public QThread{
    Q_OBJECT
public:
    typedef QString (*matrixOperation)(int, int);
    MatrixThread(QObject *parent, int min, int max, matrixOperation operation) : QThread(parent) {

    }

public slots:
    void doWork(const QString &parameter) {
        QString result = operation(minValue, maxValue);
        emit resultReady(result);
    }

signals:
    void resultReady(const QString &result);

private:
    int minValue;
    int maxValue;

    matrixOperation operation;
};

#endif // MAINWINDOW_H
