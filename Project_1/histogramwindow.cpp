#include "histogramwindow.h"
#include "ui_histogramwindow.h"

HistogramWindow::HistogramWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HistogramWindow)
{
    ui->setupUi(this);
}

HistogramWindow::HistogramWindow(QImage image1, QImage image2) :
    ui(new Ui::HistogramWindow)
    {
    ui->setupUi(this);
    numPixels = QVector<double>(256);
    int size = numPixels.size();
    for(int i = 0; i < size; i++) {
        numPixels[i] = i;
    }
    redVals = ui->Red;
    greenVals = ui->Green;
    blueVals = ui->Blue;

    MredVals = ui->MRed;
    MgreenVals = ui->MGreen;
    MblueVals = ui->MBlue;

    originalRGB = QVector<QVector<double>>(3);
    modifiedRGB = QVector<QVector<double>>(3);

    originalRGB[0] = QVector<double>(256);
    originalRGB[1] = QVector<double>(256);
    originalRGB[2] = QVector<double>(256);

    modifiedRGB[0] = QVector<double>(256);
    modifiedRGB[1] = QVector<double>(256);
    modifiedRGB[2] = QVector<double>(256);

    getRgbIntensities(&image1,
                      &originalRGB[0],
                      &originalRGB[1],
                      &originalRGB[2]);

    getRgbIntensities(&image2,
                      &modifiedRGB[0],
                      &modifiedRGB[1],
                      &modifiedRGB[2]);

    plot(redVals, originalRGB[0], "Red", Qt::red);
    plot(greenVals, originalRGB[1], "Green", Qt::green);
    plot(blueVals, originalRGB[2], "Blue", Qt::blue);

    plot(MredVals, modifiedRGB[0], "Red", Qt::red);
    plot(MgreenVals, modifiedRGB[1], "Green", Qt::green);
    plot(MblueVals, modifiedRGB[2], "Blue", Qt::blue);
}

HistogramWindow::~HistogramWindow()
{
    delete ui;
}

void HistogramWindow::getRgbIntensities(QImage * image,
                       QVector<double> * red,
                       QVector<double> * green,
                       QVector<double> * blue) {

    int imageWidth = image->width();
    int imageHeight = image->height();
    for(int y = 0; y < imageHeight; y++) {
        QRgb * rgbVals = (QRgb*)image->constScanLine(y);
        for(int x = 0; x < imageWidth; x++) {
            (*red)[qRed(rgbVals[x])]++;
            (*green)[qGreen(rgbVals[x])]++;
            (*blue)[qBlue(rgbVals[x])]++;
        }
    }
}

void HistogramWindow::plot(QCustomPlot * graph, QVector<double> values, QString name, QColor color) {
    double max;
    getMax(values, &max);

    graph->plotLayout()->insertRow(0);
    graph->plotLayout()->addElement(0, 0, new QCPTextElement(graph, name, QFont("sans", 12, QFont::Bold)));
    graph->xAxis->setRange(0, 255);
    graph->yAxis->setRange(0, max);
    QCPBars * bar = new QCPBars(graph->xAxis, graph->yAxis);
    bar->setPen(QPen(color));
    bar->setData(numPixels, values);
    graph->replot();
}

void HistogramWindow::getMax(QVector<double> values, double * max) {
    int size = values.size();
    *max = 0;

    for(int i = 0; i < size; i++) {
        double value = values[i];
        if(value > *max) {
            *max = value;
        }
    }
}
