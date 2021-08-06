#include "mainwindow.h"

#include <QApplication>
#include "wavcompression.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //wavCompression compression = wavCompression("/home/megarage9000/repos/CMPT365/Project_2_Audio/wavTestFiles/Cowbell-Mono.wav");
    // wavCompression compression = wavCompression("/home/megarage9000/repos/CMPT365/Project_2_Audio/wavTestFiles/Ensoniq-ZR-76-13-Techno-124.wav");
    wavfile file = wavfile<double>();
    file.readWavFile("/home/megarage9000/Ensoniq-ZR-76-13-Techno-124.wav");
    w.show();
    return a.exec();
}
