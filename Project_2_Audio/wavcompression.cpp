#include "wavcompression.h"


wavCompression::wavCompression()
{

}

wavCompression::wavCompression(QString fileName)
{
    fileToRead = wavfile<int>();
    fileToRead.readWavFile(fileName);

    isStereo = fileToRead.isStereo();
    if(!isStereo){
        int numSamples = fileToRead.getDataSizeInSamples();
        QVector<int> samples = fileToRead.getAmplitudes();
        for(int i = 0; i < numSamples; i++) {
            midX[i] = samples[i];
        }
    }
    compress();
}

void wavCompression::compress() {
    getMidSideChannels();
    linearPredict();
    std::cout << "Running LZWMAP\n";
    LZWMap midXCode = LZWMap(midXPredict);
    if(isStereo){
        std::cout << "Running LZWMAP side\n";
        LZWMap sideYCode = LZWMap(sideYPredict);
    }

}

void wavCompression::getMidSideChannels(){
    if(isStereo) {
        int numSamples = fileToRead.getDataSizeInSamples();
        midX = QVector<float>(numSamples);
        sideY = QVector<float>(numSamples);
        QVector<int> samplesLeft = fileToRead.getAmplitudes();
        QVector<int> samplesRight = fileToRead.getAmplitudes2();
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
    int numSamples = fileToRead.getDataSizeInSamples();
    if(isStereo) {
        midXPredict = QVector<float>(numSamples);
        sideYPredict = QVector<float>(numSamples);

        for(int i = 0; i < numSamples; i++) {
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
//            std::cout << "mid, side at " << i << ": " << midX[i] << ", " << sideY[i] << "\n";
//            std::cout << "midXPredict, sideYPredict at " << i << ": " << midXPredict[i] << ", " << sideYPredict[i] << "\n";
        }
    }
    else{
        midXPredict = QVector<float>(numSamples);
        for(int i = 0; i < numSamples; i++) {
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
//            std::cout << "midXPredict at " << i << ": " << midXPredict[i] << "\n";
        }
    }
}




