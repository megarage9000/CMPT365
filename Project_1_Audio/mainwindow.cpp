#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wavfile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open WAV file"),
                "/home/megarage9000/repos/CMPT365",
                tr("Wav files (*.wav)"));
    wavfile file(fileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

