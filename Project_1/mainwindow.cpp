#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file = BMPFile();
    image1 = ui->label;
    image2 = ui->label_2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImagesToLabels(QImage newImage1, QImage newImage2) {
    image1->setPixmap(QPixmap::fromImage(newImage1));
    image2->setPixmap(QPixmap::fromImage(newImage2));
    image1->adjustSize();
    image2->adjustSize();
}

void MainWindow::setNewImagePair() {
    if(hasImage) {
        currentImagePair[0] = imagePairs[index][0];
        currentImagePair[1] = imagePairs[index][1];
        loadImagesToLabels(currentImagePair[0], currentImagePair[1]);
        index++;
        if(index > 2) {
            index = 0;
        }
    }
}

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
    imagePairs[0][1] = grayScale.copy();

    imagePairs[1][0] = grayScale.copy();
    imagePairs[1][1] = dither.copy();

    imagePairs[2][0] = original.copy();
    imagePairs[2][1] = autoLevel.copy();
    hasImage = true;
    setNewImagePair();
}


void MainWindow::on_pushButton_clicked()
{
    setNewImagePair();
}




void MainWindow::on_pushButton_3_clicked()
{
    if(hasImage){
        HistogramWindow * window = new HistogramWindow(currentImagePair[0], currentImagePair[1]);
        window->show();
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    close();
}

