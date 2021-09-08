#ifndef WAVCOMPRESSION_H
#define WAVCOMPRESSION_H

#include "wavfile.h"
#include "wavfile.cpp"
#include "lzwmap.h"

class wavCompression
{
public:
    wavCompression(QString fileName);
    void writeSamplesToFile(QString fileName);

    LZWMap midXCode;
    LZWMap sideYCode;

    float getFileRatio();
    int getOriginalFileSize();
    int getCompressedFileSize();

private:
    void compress();
    void getMidSideChannels();
    void linearPredict(int order);
    int predictor(QVector<float> values, int maxOrder, int index);
    QString fileName;
    QString compressedLocation;
    QString uncompressedLocation;
    wavfile<int> fileToRead;
    bool isStereo;
    QVector<float> midX;
    QVector<float> sideY;

    QVector<int> midXPredict;
    QVector<int> sideYPredict;



};



#endif // WAVCOMPRESSION_H
