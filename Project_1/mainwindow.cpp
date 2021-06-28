#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/megarage9000/repos/CMPT365", tr("Image Files (*.png *.jpg *.bmp)"));
    std::cout << "File name = " << fileName.toStdString() << std::endl;
    BMPFile test = BMPFile(fileName);
    test.getAutoLevel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

