#include "wavcompression.h"


wavCompression::wavCompression()
{

}

wavCompression::wavCompression(QString fileName)
{
    fileToRead = wavfile();
    fileToRead.readWavFile(fileName);
    int numSamples = fileToRead.getDataSizeInSamples();
    QVector<double> samples = fileToRead.getAmplitudes();
    isStereo = fileToRead.isStereo();
    if(isStereo) {
        QVector<double> samples2 = fileToRead.getAmplitudes2();
        for(int i = 0; i < numSamples; i++) {
            std::cout <<  i << ": " << samples[i];
            std::cout << ", " << samples2[i] << "\n";
        }
    }
    else{
        for(int i = 0; i < numSamples; i++) {
            std::cout <<  i << ": " << samples[i] << "\n";
        }
    }

    compress();
}

void wavCompression::compress() {
    getMidSideChannels();
}

void wavCompression::getMidSideChannels(){
    if(isStereo) {
        int numSamples = fileToRead.getDataSizeInSamples();
        midX = QVector<double>(numSamples);
        sideY = QVector<double>(numSamples);
        QVector<double> samplesLeft = fileToRead.getAmplitudes();
        QVector<double> samplesRight = fileToRead.getAmplitudes2();
        for(int i = 0; i < numSamples; i++) {
            midX[i] = (samplesLeft[i] + samplesRight[i]) / 2.0f;
            sideY[i] = (samplesLeft[i] - samplesRight[i]) / 2.0f;
            std::cout << "mid, side at " << i << ": " << midX[i] << ", " << sideY[i] << "\n";
        }
   }
    else {
        std::cout << "Not Stereo\n";
    }
}





