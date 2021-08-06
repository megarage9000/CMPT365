#include "wavfile.h"
template<typename S>
wavfile<S>::wavfile()
{
}

template<typename S>
void wavfile<S>::readWavFile(QString fileName) {
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
    readSamples(&wavFile, numBytesToRead);
    std::cout << "num bytes = " << numBytesToRead << std::endl;
    wavFile.close();
}

template<typename S>
void wavfile<S>::readSamples(QFile * wavFile, int numBytesToRead){
    // For Stereo reads
    if(isStereo()) {
        dataSizeInSamples = dataSizeInSamples / 2;
        samples = QVector<S>(dataSizeInSamples);
        amplitudes = QVector<S>(dataSizeInSamples);
        amplitudes2 = QVector<S>(dataSizeInSamples);
        for(int i = 0; i < dataSizeInSamples ; i++) {

            if(numBytesToRead == 1) {
                amplitudes[i] = fromLittleEndian<qint8>(wavFile, numBytesToRead);
                amplitudes2[i] = fromLittleEndian<qint8>(wavFile, numBytesToRead);
            }
            else if(numBytesToRead == 2) {
                amplitudes[i] = fromLittleEndian<qint16_le>(wavFile, numBytesToRead);
                amplitudes2[i] = fromLittleEndian<qint16_le>(wavFile, numBytesToRead);
            }
            else{
                amplitudes[i] = fromLittleEndian<qint32_le>(wavFile, numBytesToRead);
                amplitudes2[i] = fromLittleEndian<qint32_le>(wavFile, numBytesToRead);
            }

            samples[i] = i;
            if(amplitudes[i] > highestAmplitude) {
                highestAmplitude = amplitudes[i];
            }
            if(amplitudes[i] < lowestAmplitude) {
                lowestAmplitude = amplitudes[i];
            }
            std::cout << "Amplitudes 1, 2 = " << amplitudes[i] << ", " << amplitudes2[i] << "\n";
        }
    }
    // For Mono reads
    else {
        samples = QVector<S>(dataSizeInSamples);
        amplitudes = QVector<S>(dataSizeInSamples);

        for(int i = 0; i < dataSizeInSamples ; i++) {
            if(numBytesToRead == 1) {
                amplitudes[i] = fromLittleEndian<qint8>(wavFile, numBytesToRead);
            }
            else if(numBytesToRead == 2) {
                amplitudes[i] = fromLittleEndian<qint16_le>(wavFile, numBytesToRead);
            }
            else{
                amplitudes[i] = fromLittleEndian<qint32_le>(wavFile, numBytesToRead);
            }

            samples[i] = i;
            if(amplitudes[i] > highestAmplitude) {
                highestAmplitude = amplitudes[i];
            }
            if(amplitudes[i] < lowestAmplitude) {
                lowestAmplitude = amplitudes[i];
            }
            std::cout << "Amplitudes 1 = " << amplitudes[i] << "\n";
        }
    }
}



template <typename S>
void wavfile<S>::modifyData(float startingPercent, float endPercent, int startIndex, int endIndex, QVector<double> * dest){
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

template<typename S>
void wavfile<S>::modifyDataStereo(float startingPercent, float endPercent, int startIndex, int endIndex, QVector<double> * dest, QVector<double> * dest2){
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

template<typename S>
QVector<S> wavfile<S>::getSamples() {
    return samples;
}

template<typename S>
QVector<S> wavfile<S>::getAmplitudes() {
    return amplitudes;
}

template<typename S>
QVector<S> wavfile<S>::getAmplitudes2() {
    return amplitudes2;
}

template<typename S>
int wavfile<S>::getDataSizeInSamples(){
    return dataSizeInSamples;
}

template<typename S>
int wavfile<S>::getHighestAmplitude(){
    return highestAmplitude;
}

template<typename S>
int wavfile<S>::getLowestAmplitude(){
    return lowestAmplitude;
}

template<typename S>
int wavfile<S>::getSamplesPerSecond() {
    return sampleRate;
}

template<typename S>
bool wavfile<S>::isStereo() {
    return (numChannels == 2);
}

template class wavfile<int>;
template class wavfile<double>;
