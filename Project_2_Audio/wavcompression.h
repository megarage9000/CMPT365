#ifndef WAVCOMPRESSION_H
#define WAVCOMPRESSION_H

#include "wavfile.h"

// Look at https://monkeysaudio.com/theory.html for more information
class wavCompression
{
public:
    wavCompression();
    wavCompression(QString fileName);

private:
    void compress();
    void getMidSideChannels();
    void linearPredict();

    wavfile fileToRead;
    bool isStereo;
    QVector<double> midX;
    QVector<double> sideY;


    QVector<double> midXPredict;
    QVector<double> sideYPredict;

};



#endif // WAVCOMPRESSION_H
