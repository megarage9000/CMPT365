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
    linearPredict(10);
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

int wavCompression::predictor(QVector<float> values, int maxOrder, int index){
    if(index == 0) {
        return values[0];
    }
    int numerator = 0;
    int divisor = 0;
    int start = index - (maxOrder - 1);
    if(start < 0) {
        start = 0;
    }

    for(int i = start; i < index; i++) {
        numerator += values[i];
        divisor++;
    }
    return numerator / divisor;
}

/*
    P0 = 0
    P1 = X-1
    P2 = (2 * X-1) - X-2
    P3 = (3 * X-1) - (3 *X-2) + X-3
 */
// NEEED TO REVISIT: LOOK AT CHAPTER 13 / 6 OF YOUR TEXTBOOK
void wavCompression::linearPredict(int order){

    int numSamples = fileToRead.getDataSizeInSamples();
    if(isStereo) {
        midXPredict = QVector<int>(numSamples);
        sideYPredict = QVector<int>(numSamples);

       for(int i = 0; i < numSamples; i++) {
            midXPredict[i] = predictor(midX, order, i);
            sideYPredict[i] = predictor(sideY, order, i);
       }
    }
    else{
        midXPredict = QVector<int>(numSamples);
        for(int i = 0; i < numSamples; i++) {
            midXPredict[i] = predictor(midX, order, i);
        }
    }
}




