#include "wavcompression.h"


wavCompression::wavCompression(QString fileName)
{
    // Creating the locations of our files that we will use for comparison
    this->fileName = fileName;
    this->fileName.chop(this->fileName.length() - this->fileName.lastIndexOf("/"));
    compressedLocation = this->fileName + "/compressed.txt";
    uncompressedLocation = this->fileName + "/uncompressed.txt";

    // Read wav file samples as integer
    fileToRead = wavfile<int>();
    fileToRead.readWavFile(fileName);


    isStereo = fileToRead.isStereo();

    // If not stereo, store all samples into the midX QVector
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
float wavCompression::getFileRatio(){
    int sizeCompressed = QFile(compressedLocation).size();
    int sizeNormal = QFile(uncompressedLocation).size();
    return (float)sizeNormal / sizeCompressed;
}

int wavCompression::getOriginalFileSize(){
    return QFile(uncompressedLocation).size();
}
int wavCompression::getCompressedFileSize(){
    return QFile(compressedLocation).size();
}
void wavCompression::compress() {
    getMidSideChannels();
    linearPredict(10);

    // Combines the side and mid channels into one vector
    // for compression if it is stereo
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

    // Compress using LZW compression technique
    LZWMap lzwMap = LZWMap(midSide);

    // Write the results to a file
    lzwMap.writeToFile(compressedLocation);
    // Write the original file (samples only) to file
    writeSamplesToFile(uncompressedLocation);
}

// Only applies stereo wav files
void wavCompression::getMidSideChannels(){
    if(isStereo) {
        int numSamples = fileToRead.getDataSizeInSamples();

        // Store the midX and SideY as float samples for linear predictions
        midX = QVector<float>(numSamples);
        sideY = QVector<float>(numSamples);
        QVector<int> samplesLeft = fileToRead.getAmplitudes();
        QVector<int> samplesRight = fileToRead.getAmplitudes2();
        for(int i = 0; i < numSamples; i++) {
            midX[i] = (samplesLeft[i] + samplesRight[i]) / 2.0f;
            sideY[i] = (samplesLeft[i] - samplesRight[i]) / 2.0f;
        }
   }
}

// Predictor goes as follows
// - result = 1/n (value 1 + value 2 + value 3 + ... value N - 1)
// - If the values are less than do the given order, than n would
// equal the number of values present
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

    // If Stereo, linearly predict for mid and side channels
    if(isStereo) {
        midXPredict = QVector<int>(numSamples);
        sideYPredict = QVector<int>(numSamples);

       for(int i = 0; i < numSamples; i++) {
           midXPredict[i] = midX[i] - predictor(midX, order, i);
           sideYPredict[i] = sideY[i] - predictor(sideY, order, i);
       }
    }
    // For single channel, use the unchanged samples store in midX
    else{
        midXPredict = QVector<int>(numSamples);
        for(int i = 0; i < numSamples; i++) {
            midXPredict[i] = midX[i] - predictor(midX, order, i);
        }
    }
}

// Simply writes samples to file
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




