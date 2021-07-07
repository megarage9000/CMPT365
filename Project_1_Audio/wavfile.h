#ifndef WAVFILE_H
#define WAVFILE_H

#include <QFile>
#include <QFileDialog>
#include <QtEndian>
#include <QMessageBox>
#include <iostream>

#define MAX_SAMPLES 8 * 65536

class wavfile
{
public:
    wavfile(QString fileName);
    void readWavFile(QString fileName);
    int * getData();
    void modifyData(float startingPercent, float endPercent, int startIndex, int endIndex);

private:
    int data[MAX_SAMPLES] = {};
    int numChannels;
    int sampleRate;
    int byteRate;
    int bitsPerSample;
    int dataSize;
    int dataSizeInSamples;
};

#endif // WAVFILE_H
