#include "wavfile.h"

wavfile::wavfile()
{
}

template<class convertedType>
convertedType fromLittleEndian(QFile * file, int numBytes) {
    char * bits = new char[numBytes];
    file->read(bits, numBytes);
    convertedType result = qFromLittleEndian<convertedType>((uchar*)bits);
    delete[] bits;
    return result;
}

void wavfile::readWavFile(QString fileName) {
    QFile wavFile(fileName);
    if(!wavFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    using namespace std;

    cout << "Reading WavFile...\n" ;

    // Reading done via: http://soundfile.sapp.org/doc/WaveFormat/

    // RIFF Chunk descriptor
    cout << "RIFF chunkId = " << wavFile.read(4).data() << endl;
    cout << "RIFF chunk size = " << fromLittleEndian<int>(&wavFile, 4) << endl;
    cout << "RIFF chunk format = " << wavFile.read(4).data() << endl;

    // FMT Sub-chunk
    cout << "FMT chunkId = " << wavFile.read(4).data() << endl;
    cout << "FMT chunkSize = " << fromLittleEndian<int>(&wavFile, 4) << endl;
    int FMTformat = fromLittleEndian<quint16_le>(&wavFile, 2);
    cout << "FMT audio format = " << FMTformat << endl;
    numChannels = fromLittleEndian<quint16_le>(&wavFile, 2);
    cout << "FMT num of channels = " <<  numChannels << endl;
    sampleRate = fromLittleEndian<int>(&wavFile, 4);
    cout << "FMT sample rate = " << sampleRate << endl;
    byteRate = fromLittleEndian<int>(&wavFile, 4);
    cout << "FMT byte rate = " <<  byteRate << endl;
    cout << "FMT block align = " << fromLittleEndian<quint16_le>(&wavFile, 2) << endl;
    bitsPerSample = fromLittleEndian<quint16_le>(&wavFile, 2);
    cout << "FMT bits per sample = " << bitsPerSample << endl;

    // Data Sub-chunk
    cout << "Data chunkId = " << wavFile.read(4).data() << endl;
    dataSize = fromLittleEndian<int>(&wavFile, 4);
    cout << "Data chunk size = " << dataSize << endl;

    int numBytesToRead = bitsPerSample / 8;
    dataSizeInSamples = dataSize / numBytesToRead;
    lowestAmplitude = 0;
    highestAmplitude = 0;

    // For 2 byte reads
    if(numBytesToRead == 2) {
        readSamples<qint16_le>(&wavFile, numBytesToRead);
    }
    // For 4 byte reads
    else if(numBytesToRead == 4){
        readSamples<qint32_le>(&wavFile, numBytesToRead);
    }
    wavFile.close();
}
template<class T>
void wavfile::readSamples(QFile * wavFile, int numBytesToRead){
    // For Stereo reads
    if(isStereo()) {
        dataSizeInSamples = dataSizeInSamples / 2;
        samples = QVector<double>(dataSizeInSamples);
        amplitudes = QVector<double>(dataSizeInSamples);
        amplitudes2 = QVector<double>(dataSizeInSamples);
        for(int i = 0; i < dataSizeInSamples ; i++) {
            amplitudes[i] = fromLittleEndian<T>(wavFile, numBytesToRead);
            amplitudes2[i] = fromLittleEndian<T>(wavFile, numBytesToRead);
            samples[i] = i;
            if(amplitudes[i] > highestAmplitude) {
                highestAmplitude = amplitudes[i];
            }
            if(amplitudes[i] < lowestAmplitude) {
                lowestAmplitude = amplitudes[i];
            }
        }
    }
    // For Mono reads
    else {
        samples = QVector<double>(dataSizeInSamples);
        amplitudes = QVector<double>(dataSizeInSamples);
        for(int i = 0; i < dataSizeInSamples ; i++) {
            amplitudes[i] = fromLittleEndian<T>(wavFile, numBytesToRead);
            samples[i] = i;
            if(amplitudes[i] > highestAmplitude) {
                highestAmplitude = amplitudes[i];
            }
            if(amplitudes[i] < lowestAmplitude) {
                lowestAmplitude = amplitudes[i];
            }
        }
    }
}


void wavfile::modifyData(float startingPercent, float endPercent, int startIndex, int endIndex, QVector<double> * dest){
    // We will increase the starting percent to end percent linearly
    // for dB values, as it logarithmically modifies the amplitude
    int numSamples = endIndex - startIndex;
    double rate = (double)(endPercent - startingPercent) / numSamples;
    double currentRate = startingPercent + rate;
    for(int i = startIndex; i < endIndex; i++) {
        double log = pow(10.0, (currentRate / 20.0));
        (*dest)[i] = (amplitudes[i] * log);
        currentRate += rate;
    }
}
void wavfile::modifyDataStereo(float startingPercent, float endPercent, int startIndex, int endIndex, QVector<double> * dest, QVector<double> * dest2){
    int numSamples = endIndex - startIndex;
    double rate = (double)(endPercent - startingPercent) / numSamples;
    double currentRate = startingPercent + rate;
    for(int i = startIndex; i < endIndex; i++) {
        double log = pow(10.0, (currentRate / 20.0));
        (*dest)[i] = (amplitudes[i] * log);
        (*dest2)[i] = (amplitudes2[i] * log);
        currentRate += rate;
    }
}


QVector<double> wavfile::getSamples() {
    return samples;
}

QVector<double> wavfile::getAmplitudes() {
    return amplitudes;
}

QVector<double> wavfile::getAmplitudes2() {
    return amplitudes2;
}

int wavfile::getDataSizeInSamples(){
    return dataSizeInSamples;
}

int wavfile::getHighestAmplitude(){
    return highestAmplitude;
}

int wavfile::getLowestAmplitude(){
    return lowestAmplitude;
}

int wavfile::getSamplesPerSecond() {
    return sampleRate;
}

bool wavfile::isStereo() {
    return (numChannels == 2);
}

