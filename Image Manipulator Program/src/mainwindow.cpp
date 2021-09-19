#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file = BMPFile();
    imageDisplay1 = ui->label;
    imageDisplay2 = ui->label_2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImagesToLabels(QImage Image1, QImage Image2) {
    imageDisplay1->setPixmap(QPixmap::fromImage(Image1));
    imageDisplay2->setPixmap(QPixmap::fromImage(Image2));
    imageDisplay1->adjustSize();
    imageDisplay2->adjustSize();
}

void MainWindow::setNewImagePair() {
    if(hasImage) {
        currentImagePair[0] = imagePairs[index][0];
        currentImagePair[1] = imagePairs[index][1];
        loadImagesToLabels(currentImagePair[0], currentImagePair[1]);
        index++;
        if(index > 3) {
            index = 0;
        }
    }
}

// For "New Image" Button
void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/", tr("Image Files (*.png *.jpg *.bmp)"));
    file.calculateImages(fileName);
    QImage original = file.getOriginal();
    QImage grayScale = file.getGrayScale();
    QImage dither = file.getGrayScaleDither();
    QImage autoLevel = file.getAutoLevel();

    imagePairs[0][0] = original.copy();
    imagePairs[0][1] = QImage();

    imagePairs[1][0] = original.copy();
    imagePairs[1][1] = grayScale.copy();

    imagePairs[2][0] = grayScale.copy();
    imagePairs[2][1] = dither.copy();

    imagePairs[3][0] = original.copy();
    imagePairs[3][1] = autoLevel.copy();
    hasImage = true;
    setNewImagePair();
}

// For "Next" Button
void MainWindow::on_pushButton_clicked()
{
    setNewImagePair();
}

// For "Get Histogram" Button
void MainWindow::on_pushButton_3_clicked()
{
    if(hasImage){
        HistogramWindow * window = new HistogramWindow(currentImagePair[0], currentImagePair[1]);
        window->show();
    }
}

// For "Quit" Button
void MainWindow::on_pushButton_4_clicked()
{
    close();
}

