#ifndef WAVCOMPRESSION_H
#define WAVCOMPRESSION_H

#include "wavfile.h"
#include "wavfile.cpp"
#include "lzwmap.h"

// Look at https://monkeysaudio.com/theory.html for more information
class wavCompression
{
public:
    wavCompression();
    wavCompression(QString fileName);

private:
    void compress();
    void getMidSideChannels();
    void linearPredict(int order);
    int predictor(QVector<float> values, int maxOrder, int index);

    wavfile<int> fileToRead;
    bool isStereo;
    QVector<float> midX;
    QVector<float> sideY;


    QVector<int> midXPredict;
    QVector<int> sideYPredict;

};



#endif // WAVCOMPRESSION_H
