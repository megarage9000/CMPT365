#ifndef WAVFILE_H
#define WAVFILE_H

#include <QFile>
#include <QFileDialog>
#include <QtEndian>
#include <QMessageBox>
#include <iostream>

class wavfile
{
public:
    wavfile(QString fileName);
    void readWavFile(QString fileName);
};

#endif // WAVFILE_H
