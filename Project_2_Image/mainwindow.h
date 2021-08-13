#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bmpfile.h"
#include "ycocgconversion.h"
#include "dcttransform.h"
#include "imagefilehelpers.h"
#include <QFileDialog>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_imageSelect_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
