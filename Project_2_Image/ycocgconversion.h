#ifndef YCOCGCONVERSION_H
#define YCOCGCONVERSION_H

#include <vector>
#include <QImage>

// -- Using vectors for flexibility
// use 4:2:0 downsampling
// use YCoCg converter
namespace YCoCgConversion {

    const int DOWNSAMPLE_VERT = 1;
    const int DOWNSAMPLE_HORZ = 1;

    class RGBToYCoCg {
    public:

        RGBToYCoCg(std::vector<std::vector<QRgb>> rgbs);

        std::vector<std::vector<int>> Y;
        std::vector<std::vector<int>> Co;
        std::vector<std::vector<int>> Cg;
    };

    class YCoCgToRGB {
    public:
        YCoCgToRGB(
                std::vector<std::vector<int>> Y,
                std::vector<std::vector<int>> Co,
                std::vector<std::vector<int>> Cg
        );
        std::vector<std::vector<QRgb>> rgbs;
    };
}

#endif // YCOCGCONVERSION_H
