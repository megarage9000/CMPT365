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

int wavCompression::quantizer(int value, int range){
    if(value < 0) {
        return -floor(value / range + 0.5);
    }
    else {
        return floor(value / range + 0.5);
    }

}

// NEEED TO REVISIT: LOOK AT CHAPTER 13 / 6 OF YOUR TEXTBOOK
void wavCompression::linearPredict(int order){

    int numSamples = fileToRead.getDataSizeInSamples();
    int range = fileToRead.getHighestAmplitude() - fileToRead.getLowestAmplitude();
    if(isStereo) {
        midXPredict = QVector<int>(numSamples);
        sideYPredict = QVector<int>(numSamples);

       for(int i = 0; i < numSamples; i++) {
//            midXPredict[i] = quantizer(midX[i] - predictor(midX, order, i), range);
//            sideYPredict[i] = quantizer(sideY[i] - predictor(sideY, order, i), range);
           midXPredict[i] = midX[i] - predictor(midX, order, i);
           sideYPredict[i] = sideY[i] - predictor(sideY, order, i);
       }
    }
    else{
        midXPredict = QVector<int>(numSamples);
        for(int i = 0; i < numSamples; i++) {
//            midXPredict[i] = quantizer(midX[i] - predictor(midX, order, i), range);
            midXPredict[i] = midX[i] - predictor(midX, order, i);
        }
    }
}




