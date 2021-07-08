#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <bmpfile.h>
#include <histogramwindow.h>
#include <iostream>
#include <QLabel>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setNewImagePair();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    void loadImagesToLabels(QImage image1, QImage image2);
    Ui::MainWindow *ui;
    BMPFile file;
    QLabel * image1;
    QLabel * image2;
    QImage imagePairs[3][2];
    QImage currentImagePair[2];
    int index = 0;
    bool hasImage = false;
};
#endif // MAINWINDOW_H
