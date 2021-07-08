#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file =  new wavfile();
    plot = ui->widget;
    plot2 = ui->widget_2;

    plot->xAxis->setLabel("Samples");
    plot->yAxis->setLabel("Amplitude");
    plot->addGraph();
    plot2->xAxis->setLabel("Samples");
    plot2->yAxis->setLabel("Amplitude");
    plot2->addGraph();
    plot2->graph(0)->setPen(QPen(Qt::red));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Using QCustomPlot library to display waveform
void MainWindow::plotWavFile() {
    int numSamples = file->getDataSizeInSamples();
    int amplitudeRange = file->getHighestAmplitude() - file->getLowestAmplitude();

    // Calculating & plotting the modified wav file
    QVector<double> modifiedAmplitudes = QVector<double>(numSamples);
    QVector<double> samples = file->getSamples();
    // Calculating fade in from -20db -> 0db
    file->modifyData(-20, 0, 0, numSamples / 2, &modifiedAmplitudes);
    // Calculating fade out from 0db -> -20db
    file->modifyData(0, -20, numSamples / 2, numSamples, &modifiedAmplitudes);
    plot->graph(0)->setData(samples, modifiedAmplitudes);
    plot->yAxis->setRange(-1.5 * amplitudeRange, 1.5 * amplitudeRange);
    plot->xAxis->setRange(-.5 * numSamples, 1.5 * numSamples);

    // Plotting the original data
    QVector<double> amplitudes = file->getAmplitudes();
    plot2->graph(0)->setData(samples, amplitudes);
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
                "/",
                tr("Wav files (*.wav)"));
    file->readWavFile(fileName);
    plotWavFile();
}

