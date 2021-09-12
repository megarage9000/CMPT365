#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fileSelect_clicked()
{
    ui->compressionResult->setText("Calculating...");
    QString fileName = QFileDialog::getOpenFileName(this,
                    tr("Open Wav file"), "", tr("Wav files(*.wav)"));
    wavCompression compression = wavCompression(fileName);
    QString resultString = "Original file size = " +
                            QString::number(compression.getOriginalFileSize()) +
                            ", Compressed file size = " +
                            QString::number(compression.getCompressedFileSize()) +
                            ", Ratio = " + QString::number(compression.getFileRatio());
    ui->compressionResult->setText(resultString);
}

