#include "wavfile.h"

wavfile::wavfile(QString fileName)
{
    samples = QVector<double>(MAX_SAMPLES);
    amplitudes = QVector<double>(MAX_SAMPLES);
    readWavFile(fileName);
}

template<class convertedType>
convertedType fromLittleEndian(QFile * file, int numBytes) {
    char * bits = new char[numBytes];
    file->read(bits, numBytes);
    convertedType result = qFromLittleEndian<convertedType>((uchar*)bits);
    free(bits);
    return result;
}

void wavfile::readWavFile(QString fileName) {
    QFile wavFile(fileName);
    if(!wavFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    using namespace std;

    cout << "Reading WavFile...\n" ;

    // Read via: http://soundfile.sapp.org/doc/WaveFormat/

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
    if(numBytesToRead == 2) {
        for(int i = 0; i < dataSizeInSamples ; i++) {
            amplitudes[i] = fromLittleEndian<qint16_le>(&wavFile, numBytesToRead);
            samples[i] = i;
            if(amplitudes[i] > highestAmplitude) {
                highestAmplitude = amplitudes[i];
            }
            if(amplitudes[i] < lowestAmplitude) {
                lowestAmplitude = amplitudes[i];
            }
        }
    }
    else{
        for(int i = 0; i < dataSizeInSamples ; i++) {
            amplitudes[i] = fromLittleEndian<qint32_le>(&wavFile, numBytesToRead);
            samples[i] = i;
            if(amplitudes[i] > highestAmplitude) {
                highestAmplitude = amplitudes[i];
            }
            if(amplitudes[i] < lowestAmplitude) {
                lowestAmplitude = amplitudes[i];
            }
        }
    }
    wavFile.close();
}


void wavfile::modifyData(float startingPercent, float endPercent, int startIndex, int endIndex){
    // We will increase the starting percent to end percent linearly
    int numSamples = endIndex - startIndex;
    int rate = (endPercent - startingPercent) / numSamples;
    for(int i = 0; i < numSamples; i++) {

    }

}

QVector<double> wavfile::getSamples() {
    return samples;
}

QVector<double> wavfile::getAmplitudes() {
    return amplitudes;
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


