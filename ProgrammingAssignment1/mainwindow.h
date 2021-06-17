#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include "matrixlift.h"
#include "textthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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
    void appendMatrixLiftingOutput(const QString &output);
    void appendMatrixMultiplicationOutput(const QString &output);

private:
    Ui::MainWindow *ui;
    TextThread *textThreadLifting;
    TextThread *textThreadMultiplication;

};
#endif // MAINWINDOW_H
