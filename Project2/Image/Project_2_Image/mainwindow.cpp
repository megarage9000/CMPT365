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
    QString modifiedImageLocation = fileLocation;

    modifiedImageLocation.chop(modifiedImageLocation.length() - modifiedImageLocation.lastIndexOf("/"));
    QString dctResultsLocation = modifiedImageLocation;
    modifiedImageLocation += "/modifiedImage.bmp";


    BMPFile file = BMPFile(fileLocation);

    YCoCgConversion::RGBToYCoCg conversionA = YCoCgConversion::RGBToYCoCg(file.getRgbs());
    dctTransform transformY = dctTransform(conversionA.Y, false);
    dctTransform transformCo = dctTransform(conversionA.Co, false);
    dctTransform transformCg = dctTransform(conversionA.Cg, false);

    // Write results to file
    QFile YData = QFile(dctResultsLocation + "/YDctResults.txt");
    QFile CoData = QFile(dctResultsLocation + "/CoDctResults.txt");
    QFile CgData = QFile(dctResultsLocation + "/CgDctResults.txt");



    // Y File
    if(YData.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream stream(&YData);
        stream << "Y DCT DATA \n";
        std::vector<std::vector<int>> results = transformY.result;
        int width = results[0].size();
        int height = results.size();

        for(int row = 0; row < height; row++) {
            std::vector<int> rowToRead = results[row];
            for(int col = 0; col < width; col++) {
                stream << rowToRead[col];
                stream << " ";

            }
            stream << "\n";
        }
        YData.close();
    }

    // Co File
    if(CoData.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream stream(&CoData);
        stream << "Co DCT DATA \n";
        std::vector<std::vector<int>> results = transformCo.result;
        int width = results[0].size();
        int height = results.size();

        for(int row = 0; row < height; row++) {
            std::vector<int> rowToRead = results[row];
            for(int col = 0; col < width; col++) {
                stream << rowToRead[col];
                stream << " ";

            }
            stream << "\n";
        }
        CoData.close();
    }

    // Cg File
    if(CgData.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream stream(&CgData);
        stream << "Cg DCT DATA \n";
        std::vector<std::vector<int>> results = transformCg.result;
        int width = results[0].size();
        int height = results.size();

        for(int row = 0; row < height; row++) {
            std::vector<int> rowToRead = results[row];
            for(int col = 0; col < width; col++) {
                stream << rowToRead[col];
                stream << " ";

            }
            stream << "\n";
        }
        CgData.close();
    }

    YCoCgConversion::YCoCgToRGB conversionBA = YCoCgConversion::YCoCgToRGB(
                    dctTransform(transformY.result, true).result,
                    dctTransform(transformCo.result, true).result,
                    dctTransform(transformCg.result, true).result
                );


    ImageHelpers::saveImage(modifiedImageLocation, conversionBA.rgbs);

    QPixmap modifiedImg = QPixmap(modifiedImageLocation);
    QPixmap originalImg = QPixmap(fileLocation);

    ui->modified->setPixmap(modifiedImg);

    ui->original->setPixmap(originalImg);
}

