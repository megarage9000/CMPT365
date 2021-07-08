#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file = nullptr;
    plot = ui->widget;
    plot2 = ui->widget_2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Using QCustomPlot library to display waveform
void MainWindow::plotWavFile() {
    int numSamples = file->getDataSizeInSamples();
    int amplitudeRange = file->getHighestAmplitude() - file->getLowestAmplitude();
    QVector<double> modifiedAmplitudes = QVector<double>(numSamples);
    QVector<double> samples = file->getSamples();

    file->modifyData(0, -20, 0, numSamples / 2, &modifiedAmplitudes);
    file->modifyData(-20, 0, numSamples / 2, numSamples, &modifiedAmplitudes);
    plot->addGraph();
    plot->graph(0)->setData(samples, modifiedAmplitudes);
    plot->xAxis->setLabel("Samples");
    plot->yAxis->setLabel("Amplitude");
    plot->xAxis2->setLabel("Modified WAV File");
    plot->yAxis->setRange(-1.5 * amplitudeRange, 1.5 * amplitudeRange);
    plot->xAxis->setRange(-.5 * numSamples, 1.5 * numSamples);

    QVector<double> amplitudes = file->getAmplitudes();
    plot2->addGraph();
    plot2->graph(0)->setData(samples, amplitudes);
    plot2->graph(0)->setPen(QPen(Qt::red));
    plot2->xAxis->setLabel("Samples");
    plot2->yAxis->setLabel("Amplitude");
    plot2->xAxis2->setLabel("Original WAV File");
    plot2->yAxis->setRange(-1.5 * amplitudeRange, 1.5 * amplitudeRange);
    plot2->xAxis->setRange(-.5 * numSamples, 1.5 * numSamples);

    plot2->replot();
    plot->replot();



}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open WAV file"),
                "/home/megarage9000/repos/CMPT365",
                tr("Wav files (*.wav)"));
    file = new wavfile(fileName);
    plotWavFile();
}

