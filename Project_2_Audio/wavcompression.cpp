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
//    if(isStereo) {
//        QVector<double> samples2 = fileToRead.getAmplitudes2();
//        for(int i = 0; i < numSamples; i++) {
//            std::cout <<  i << ": " << samples[i];
//            std::cout << ", " << samples2[i] << "\n";
//        }
//    }
//    else{
//        for(int i = 0; i < numSamples; i++) {
//            std::cout <<  i << ": " << samples[i] << "\n";
//        }
//    }

    compress();
}

void wavCompression::compress() {
    getMidSideChannels();
    linearPredict();
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
            //std::cout << "mid, side at " << i << ": " << midX[i] << ", " << sideY[i] << "\n";
        }
   }
    else {
        std::cout << "Not Stereo\n";
    }
}

/*
    P0 = 0
    P1 = X-1
    P2 = (2 * X-1) - X-2
    P3 = (3 * X-1) - (3 *X-2) + X-3
 */
void wavCompression::linearPredict(){
    int order = 3;
    int numSamples = fileToRead.getDataSizeInSamples();
    if(isStereo) {
        midXPredict = QVector<double>(numSamples);
        sideYPredict = QVector<double>(numSamples);

        for(int i = 0; i < numSamples; i+= order) {
            switch(i) {
                case 0:
                    midXPredict[i] = midX[i] - 0;
                    sideYPredict[i] = sideY[i] - 0;
                    break;
                case 1:
                    midXPredict[i] = midX[i] - (midX[i - 1]);
                    sideYPredict[i] = sideY[i] - (sideY[i - 1]);
                    break;
                case 2:
                    midXPredict[i] = midX[i] - (2 * midX[i - 1] - midX[i - 2]);
                    sideYPredict[i] = sideY[i] - (2 * sideY[i - 1] - sideY[i - 2]);
                    break;
                default:
                    midXPredict[i] = midX[i] - (3 * midX[i - 1] - 3 * midX[i - 2] + midX[i - 3]);
                    sideYPredict[i] = sideY[i] - (3 * sideY[i - 1] - 3 * sideY[i - 2] + sideY[i - 3]);
                    break;
            }
            std::cout << "midXPredict, sideYPredict at " << i << ": " << midXPredict[i] << ", " << sideYPredict[i] << "\n";
        }
    }
    else{
        midXPredict = QVector<double>(numSamples);
        for(int i = 0; i < numSamples; i+= order) {
            switch(i) {
                case 0:
                    midXPredict[i] = midX[i] - 0;
                    break;
                case 1:
                    midXPredict[i] = midX[i] - (midX[i - 1]);
                    break;
                case 2:
                    midXPredict[i] = midX[i] - (2 * midX[i - 1] - midX[i - 2]);
                    break;
                default:
                    midXPredict[i] = midX[i] - (3 * midX[i - 1] - 3 * midX[i - 2] + midX[i - 3]);
                    break;
            }
            std::cout << "midXPredict at " << i << ": " << midXPredict[i] << "\n";
        }
    }
}



