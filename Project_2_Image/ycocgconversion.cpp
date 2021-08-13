#include "ycocgconversion.h"

namespace YCoCgConversion {

    RGBToYCoCg::RGBToYCoCg(std::vector<std::vector<QRgb>> rgbs)
    {
        Y = std::vector<std::vector<int>>();
        Co = std::vector<std::vector<int>>();
        Cg = std::vector<std::vector<int>>();

        int width = rgbs[0].size();
        int height = rgbs.size();

        std::vector<int> YRow;
        std::vector<int> CoRow;
        std::vector<int> CgRow;

        for(int row = 0; row < height; row++) {
            YRow = std::vector<int>();

            // Create Co / Cg rows if row is multiple of 2
            if(row % DOWNSAMPLE_VERT == 0) {
                CoRow = std::vector<int>();
                CgRow = std::vector<int>();
            }
            for(int col = 0; col < width; col++) {
                QRgb value = rgbs[row][col];

                int red = qRed(value);
                int green = qGreen(value);
                int blue = qBlue(value);

                int CoVal = red / 2.0f - blue / 2.0f; // Co
                int CgVal = green / 2.0f - blue / 4.0f - red / 4.0f; // Cg
                int YVal =  green / 2.0f + blue / 4.0f + red / 4.0f; // Y

                YRow.push_back(YVal);

                // Add values if row and col are multiples of 2
                if(row % DOWNSAMPLE_VERT == 0 && col % DOWNSAMPLE_HORZ == 0) {
                    CoRow.push_back(CoVal);
                    CgRow.push_back(CgVal);
                }
            }

            Y.push_back(YRow);
            if(row % DOWNSAMPLE_HORZ == 0) {
                Co.push_back(CoRow);
                Cg.push_back(CgRow);
            }
        }
    }


    YCoCgToRGB::YCoCgToRGB(std::vector<std::vector<int>> Y,
                           std::vector<std::vector<int>> Co,
                           std::vector<std::vector<int>> Cg)
    {
        int width = Y[0].size();
        int height = Y.size();

        rgbs = std::vector<std::vector<QRgb>>();

        std::vector<int> CoRow = Co[0];
        std::vector<int> CgRow = Cg[0];

        int CgVal = CoRow[0];
        int CoVal = CgRow[0];

        for(int row = 0; row < height; row++) {

            if(row % DOWNSAMPLE_VERT == 0) {
                CoRow = Co[row / DOWNSAMPLE_VERT];
                CgRow = Cg[row / DOWNSAMPLE_VERT];
            }

            std::vector<QRgb> rgbRow = std::vector<QRgb>();

            for(int col = 0; col < width; col++) {

                if(row % DOWNSAMPLE_VERT == 0 && col % DOWNSAMPLE_HORZ == 0) {
                    CgVal = CgRow[col / DOWNSAMPLE_HORZ];
                    CoVal = CoRow[col / DOWNSAMPLE_HORZ];
                }
                int YVal = Y[row][col];

                int red = -CgVal + YVal + CoVal;
                int green = CgVal + YVal;
                int blue = -CgVal + YVal - CoVal;

                QRgb rgbVal = qRgb(red, green, blue);
                rgbRow.push_back(rgbVal);
            }

            rgbs.push_back(rgbRow);

        }

    }
}


















