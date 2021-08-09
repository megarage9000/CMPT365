#include "mainwindow.h"

#include <QApplication>
#include "wavcompression.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //wavCompression compression = wavCompression("/home/megarage9000/repos/CMPT365/Project_2_Audio/wavTestFiles/Cowbell-Mono.wav");
    wavCompression compression = wavCompression("/home/megarage9000/repos/CMPT365/Project_2_Audio/wavTestFiles/Cowbell-Mono.wav");
    w.show();
    return a.exec();
}
