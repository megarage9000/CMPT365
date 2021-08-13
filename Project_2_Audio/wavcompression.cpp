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
    QVector<int> midSide;
    if(isStereo){
       int size = fileToRead.getDataSizeInSamples() * 2;
       midSide = QVector<int>();
       for(int i = 0; i < size; i++) {
           if(i % 2 == 0) {
               midSide.push_back(sideYPredict[i / 2]);
           }
           else{
               midSide.push_back(midXPredict[i / 2]);
           }
       }
    }
    else{
        midSide = midXPredict;
    }

    LZWMap lzwMap = LZWMap(midSide);
    lzwMap.writeToFile("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/samplesCompressed.txt");
    writeSamplesToFile("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/samples.txt");

    int sizeCompressed = QFile("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/samplesCompressed.txt").size();
    int sizeNormal = QFile("/home/megarage9000/repos/CMPT365/Project_2_test_files/Project2/samples.txt").size();

    std::cout << "Compressed = " << sizeCompressed << ", Uncompressed = " << sizeNormal << ", ratio = " << (float)sizeNormal/sizeCompressed << "\n";
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

void wavCompression::linearPredict(int order){

    int numSamples = fileToRead.getDataSizeInSamples();
    if(isStereo) {
        midXPredict = QVector<int>(numSamples);
        sideYPredict = QVector<int>(numSamples);

       for(int i = 0; i < numSamples; i++) {
           midXPredict[i] = midX[i] - predictor(midX, order, i);
           sideYPredict[i] = sideY[i] - predictor(sideY, order, i);
       }
    }
    else{
        midXPredict = QVector<int>(numSamples);
        for(int i = 0; i < numSamples; i++) {
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




