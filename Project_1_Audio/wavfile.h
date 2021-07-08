#ifndef WAVFILE_H
#define WAVFILE_H

#include <QFile>
#include <QtEndian>
#include <iostream>
#include <tgmath.h>

class wavfile
{
public:
    wavfile();
    void readWavFile(QString fileName);
    void modifyData(float startingPercent, float endPercent, int startIndex, int endIndex, QVector<double> * dest);
    QVector<double> getSamples();
    QVector<double> getAmplitudes();
    int getDataSizeInSamples();
    int getLowestAmplitude();
    int getHighestAmplitude();

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
    QVector<double> samples;
    // The actual sample data
    QVector<double> amplitudes;
};

#endif // WAVFILE_H
