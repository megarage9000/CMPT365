#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>

namespace Ui {
class HistogramWindow;
}

class HistogramWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HistogramWindow(QWidget *parent = nullptr);
    ~HistogramWindow();
    HistogramWindow(QImage image1, QImage image2);
    void getRgbIntensities(QImage * image,
                           QVector<double> * red,
                           QVector<double> * green,
                           QVector<double> * blue);
    void plot(QCustomPlot * graph, QVector<double> values, QString name, QColor color);
    void getMax(QVector<double> values, double * max);
private:
    Ui::HistogramWindow *ui;
    QVector<QVector<double>> originalRGB;
    QVector<QVector<double>> modifiedRGB;
    QVector<double> numPixels;

    // RGB values from original
    QCustomPlot * redVals;
    QCustomPlot * greenVals;
    QCustomPlot * blueVals;

    // RGB values from modified
    QCustomPlot * MredVals;
    QCustomPlot * MgreenVals;
    QCustomPlot * MblueVals;

};

#endif // HISTOGRAMWINDOW_H
