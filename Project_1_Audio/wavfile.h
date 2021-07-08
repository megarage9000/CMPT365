#ifndef WAVFILE_H
#define WAVFILE_H

#include <QFile>
#include <QFileDialog>
#include <QtEndian>
#include <QMessageBox>
#include <iostream>
#include <tgmath.h>

#define MAX_SAMPLES 8 * 65536

class wavfile
{
public:
    wavfile(QString fileName);
    void readWavFile(QString fileName);
    int * getData();
    void modifyData(float startingPercent, float endPercent, int startIndex, int endIndex, QVector<double> * dest);
    void normalizeDataSamples(int start, int end);
    void normalizeDataAmplitudes(int start, int end);
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
    QVector<double> samples;
    QVector<double> amplitudes;
};

#endif // WAVFILE_H
