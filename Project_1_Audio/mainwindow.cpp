#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    file = new wavfile(fileName);
    plot = ui->widget;
    plotWavFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotWavFile() {
    QVector<double> samples = file->getSamples();
    QVector<double> amplitudes = file->getAmplitudes();

    plot->addGraph();
    plot->graph(0)->setData(samples, amplitudes);
    plot->xAxis->setLabel("Samples");
    plot->yAxis->setLabel("Amplitude");
    plot->yAxis->setRange(file->getLowestAmplitude(), file->getHighestAmplitude());
    plot->xAxis->setRange(0, file->getDataSizeInSamples());
    plot->replot();
}
