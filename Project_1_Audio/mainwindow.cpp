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
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::red));
    plot2->xAxis->setLabel("Samples");
    plot2->yAxis->setLabel("Amplitude");
    plot2->addGraph();
    plot2->addGraph();
    plot2->graph(0)->setPen(QPen(Qt::red));

    sampleRateOriginal =  new QCPTextElement(plot2, "", QFont("sans", 12, QFont::Bold));
    plot2->plotLayout()->insertRow(0);
    plot2->plotLayout()->addElement(0, 0, sampleRateOriginal);

    sampleRateModified = new QCPTextElement(plot, "", QFont("sans", 12, QFont::Bold));
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, sampleRateModified);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Using QCustomPlot library to display waveform
void MainWindow::plotWavFile() {
    int numSamples = file->getDataSizeInSamples();
    int amplitudeRange = file->getHighestAmplitude() - file->getLowestAmplitude();
    isStereo = file->isStereo();
    QVector<double> samples = file->getSamples();
    plot->graph(0)->data()->clear();
    plot->graph(1)->data()->clear();
    plot2->graph(0)->data()->clear();
    plot2->graph(1)->data()->clear();

    // Calculating & plotting the modified wav file
    sampleRateModified->setText("Sampling rate = " + QString::number(file->getSamplesPerSecond()) + " Samples per second");
    QVector<double> modifiedAmplitudes = QVector<double>(numSamples);
    // - stereo
    if(isStereo) {
        QVector<double> modifiedAmplitudes2 = QVector<double>(numSamples);
        // Calculating fade in from -20db -> 0db
        file->modifyDataStereo(-20, 0, 0, numSamples / 2, &modifiedAmplitudes, &modifiedAmplitudes2);
        // Calculating fade out from 0db -> -20db
        file->modifyDataStereo(0, -20, numSamples / 2, numSamples, &modifiedAmplitudes, &modifiedAmplitudes2);
        plot->graph(1)->setData(samples, modifiedAmplitudes2);
    }
    // - mono
    else {
        // Calculating fade in from -20db -> 0db
        file->modifyData(-20, 0, 0, numSamples / 2, &modifiedAmplitudes);
        // Calculating fade out from 0db -> -20db
        file->modifyData(0, -20, numSamples / 2, numSamples, &modifiedAmplitudes);
    }
    plot->graph(0)->setData(samples, modifiedAmplitudes);
    plot->yAxis->setRange(-1.5 * amplitudeRange, 1.5 * amplitudeRange);
    plot->xAxis->setRange(-.5 * numSamples, 1.5 * numSamples);

    // Plotting the original data
    sampleRateOriginal->setText("Sampling rate " + QString::number(file->getSamplesPerSecond()) + " Samples per second");
    QVector<double> amplitudes = file->getAmplitudes();
    // - stereo
    if(isStereo) {
        QVector<double> amplitudes2 = file->getAmplitudes2();
        plot2->graph(1)->setData(samples, amplitudes2);
    }
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


void MainWindow::toggleVisiblity(QCustomPlot * plot, int index) {
    if(isStereo) {
        if(plot->graph(index)->visible()) {
            plot->graph(index)->setVisible(false);
        }
        else {
            plot->graph(index)->setVisible(true);
        }
        plot->replot();
    }
}

// For Stereo WAV formats, toggle sample visibility

// - Modified WAV
void MainWindow::on_pushButton_2_clicked()
{
    toggleVisiblity(plot2, 0);
}


void MainWindow::on_pushButton_3_clicked()
{
    toggleVisiblity(plot2, 1);
}

// - Original
void MainWindow::on_pushButton_5_clicked()
{
    toggleVisiblity(plot, 0);
}


void MainWindow::on_pushButton_4_clicked()
{
    toggleVisiblity(plot, 1);
}

