#ifndef WAVFILE_H
#define WAVFILE_H

#include <QFile>
#include <iostream>
#include <tgmath.h>
#include "fromLittleEndian.h"

template<typename S>
class wavfile
{
public:
    wavfile();
    void readWavFile(QString fileName);
    void modifyData(float startingPercent, float endPercent, int startIndex, int endIndex, QVector<double> * dest);
    void modifyDataStereo(float startingPercent, float endPercent, int startIndex, int endIndex, QVector<double> * dest, QVector<double> * dest2);
    QVector<S> getSamples();
    QVector<S> getAmplitudes();
    QVector<S> getAmplitudes2();
    int getDataSizeInSamples();
    int getLowestAmplitude();
    int getHighestAmplitude();
    int getSamplesPerSecond();
    bool isStereo();
    void readSamples(QFile * wavFile, int numBytesToRead);


private:
    int numChannels;
    int sampleRate;
    int byteRate;
    int bitsPerSample;
    int dataSize;
    int dataSizeInSamples;
    int lowestAmplitude;
    int highestAmplitude;
    // Not to be confused with the actual data,
    // samples just indicate the index of the given
    // amplitude. QCustomPlot needs it
    QVector<S> samples;
    // The actual sample data
    QVector<S> amplitudes;
    // If it is stereo
    QVector<S> amplitudes2;

};



#endif // WAVFILE_H
