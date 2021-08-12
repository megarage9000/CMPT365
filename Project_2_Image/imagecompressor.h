#ifndef IMAGECOMPRESSOR_H
#define IMAGECOMPRESSOR_H


#include <bmpfile.h>

class imageCompressor
{
public:
    imageCompressor(BMPFile file);

private:
    // use 4:2:0 downsampling
    // use YCoCg converter
    void convertToYCov(BMPFile);

    std::vector<std::vector<int>> Y;
    std::vector<std::vector<int>> Co;
    std::vector<std::vector<int>> Cg;

};

#endif // IMAGECOMPRESSOR_H
