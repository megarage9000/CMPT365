#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include "matrixthread.h"
#include "matrixlift.h"


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
};



#endif // MAINWINDOW_H
