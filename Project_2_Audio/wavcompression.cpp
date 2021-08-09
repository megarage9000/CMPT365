#include "wavcompression.h"


wavCompression::wavCompression(QString fileName)
{
    fileToRead = wavfile<int>();
    fileToRead.readWavFile(fileName);

    isStereo = fileToRead.isStereo();
    if(!isStereo){
        int numSamples = fileToRead.getDataSizeInSamples();
        midX = QVector<float>(numSamples);
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
//    midXCode = LZWMap(midXPredict);
//    midXCode.writeToFile("midXCode.txt");
    evx::entropy_coder coder;
    evx::bitstream midXStream(midXPredict.data(), midXPredict.size());
    evx::bitstream midXStreamCode(midXPredict.size());
    coder.encode(&midXStream, &midXStreamCode);

    QFile midXFile("midXCode.txt");

    if(midXFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&midXFile);

        out << midXStreamCode.query_data();
    }

    writeSamplesToFile("samples.txt");
    QFile samplesFile("samples.txt");

    if(isStereo){
//        sideYCode = LZWMap(sideYPredict);
//        sideYCode.writeToFile("sideYCode.txt");

        QFile sideYFile("sideYCode.txt");

        int sizeOfCode = sideYFile.size() + midXFile.size();
        int sizeOfSamples = samplesFile.size();

        std::cout << "Samples size in bytes = " << sizeOfSamples
                  << ", size of coded sequence = " << sizeOfCode
                  << ", Compression Ratio = " << (float)sizeOfSamples / sizeOfCode
                  << "\n";

    }
    else {
        int sizeOfCode = midXFile.size();
        int sizeOfSamples = samplesFile.size();

        std::cout << "Samples size in bytes = " << sizeOfSamples
                  << ", size of coded sequence = " << sizeOfCode
                  << ", Compression Ratio = " << (float)sizeOfSamples / sizeOfCode
                  << "\n";

    }

    midXFile.close();
    samplesFile.close();

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

void wavCompression::writeSamplesToFile(QString fileName) {
    QFile file(fileName);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        QVector<int> samples = fileToRead.getAmplitudes();
        int length = samples.size();
        for(int i = 0; i < length; i++) {
            out << samples[i];
        }
        if(isStereo) {
            QVector<int> samplesRight = fileToRead.getAmplitudes2();
            int lengthRight = samplesRight.size();
            for(int i = 0; i < lengthRight; i++) {
                out << samplesRight[i];
            }
        }

        file.close();
    }
    else {
        return;
    }
}




