#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_imageSelect_clicked()
{
    QString fileLocation = QFileDialog::getOpenFileName(this, tr("Choose image"),
                                                        "", tr("Images (*.bmp)"));

    BMPFile file = BMPFile(fileLocation);

    YCoCgConversion::RGBToYCoCg conversionA = YCoCgConversion::RGBToYCoCg(file.getRgbs());
    dctTransform transformY = dctTransform(conversionA.Y, false);
    dctTransform transformCo = dctTransform(conversionA.Co, false);
    dctTransform transformCg = dctTransform(conversionA.Cg, false);

    YCoCgConversion::YCoCgToRGB conversionBA = YCoCgConversion::YCoCgToRGB(
                    dctTransform(transformY.result, true).result,
                    dctTransform(transformCo.result, true).result,
                    dctTransform(transformCg.result, true).result
                );

    QString modifiedImageLocation = fileLocation;
    modifiedImageLocation.chop(modifiedImageLocation.length() - modifiedImageLocation.lastIndexOf("/"));
    modifiedImageLocation += "/modifiedImage.bmp";

    ImageHelpers::saveImage(modifiedImageLocation, conversionBA.rgbs);

    QPixmap modifiedImg = QPixmap(modifiedImageLocation);
    QPixmap originalImg = QPixmap(fileLocation);

    ui->modified->setPixmap(modifiedImg);

    ui->original->setPixmap(originalImg);
}

