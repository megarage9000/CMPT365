#ifndef WAVCOMPRESSION_H
#define WAVCOMPRESSION_H

#include "wavfile.h"


class wavCompression
{
public:
    wavCompression();
    wavCompression(QString fileName);

private:
    void compress();
    void getMidSideChannels();
    wavfile fileToRead;
    bool isStereo;
    QVector<double> midX;
    QVector<double> sideY;
};



#endif // WAVCOMPRESSION_H
