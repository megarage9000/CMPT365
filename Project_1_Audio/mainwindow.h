#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "wavfile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // Try waveplot form: https://stackoverflow.com/questions/50277132/qt-audio-file-to-wave-like-audacity
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void plotWavFile();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QCustomPlot * plot;
    QCustomPlot * plot2;
    wavfile * file;
};
#endif // MAINWINDOW_H
