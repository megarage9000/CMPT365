#include "dcttransform.h"



dctTransform::dctTransform(std::vector<std::vector<int>> values)
{
    int width = values[0].size();
    int height = values.size();

}

std::vector<std::vector<double>> dctTransform::getTranspose(std::vector<std::vector<double>> inputMatrix) {
    std::vector<std::vector<double>> transpose;

    int rowLength = inputMatrix[0].capacity();
    int colLength = inputMatrix.capacity();

    for(int i = 0; i < colLength; i++) {
        std::vector<double> newRow;
        for(int j = 0; j < rowLength; j++) {
            newRow.push_back(inputMatrix[j][i]);
        }
        transpose.push_back(newRow);
    }
    return transpose;
}

double dctTransform::getDctTransform(int i, int j, int n) {
    double a = (i == 0) ? (sqrt(1.0 / n)) : (sqrt(2.0 / n));
    double numerator = ((2 * j  + 1) * i * M_PI);
    double denominator = (2 * n);
    return a * cos(numerator / denominator);
}


std::vector<std::vector<double>> createSubMatrix(std::vector<std::vector<int>> values, int rowStart, int colStart, int rowEnd, int colEnd){
    std::vector<std::vector<double>> vectorToReturn = std::vector<std::vector<double>>();

    for(int row = rowStart; row < rowStart + DIMENSION; row++){
        std::vector<double> rowToAdd =std::vector<double>();
        if(row > rowEnd) {
            for(int i = 0; i < DIMENSION; i++){
                rowToAdd.push_back(EMPTY_VALUE);
            }
        }
        else{
            for(int col = colStart; col < colStart + DIMENSION; col++){
                if(col > colEnd){
                    rowToAdd.push_back(EMPTY_VALUE);
                }
                else{
                    rowToAdd.push_back(values[row][col]);
                }
            }
        }
        vectorToReturn.push_back(rowToAdd);
    }
    return vectorToReturn;
}

void mapMatrixValues(std::vector<std::vector<int>> * dest, std::vector<std::vector<double>> * source, int rowStart, int colStart, int rowEnd, int colEnd){

    int sourceMaxWidth = source->at(0).size();
    int sourceMaxHeight = source->size();

    int sourceRow = 0;
    int sourceCol = 0;

    for(int row = rowStart; row <= rowEnd; row++){

        for(int col = colStart; col <= colEnd; col++){
            dest->at(row)[col] = source->at(sourceRow)[sourceCol];
            sourceCol++;
            if(sourceCol >= sourceMaxWidth){
                break;
            }
        }

        sourceCol = 0;
        sourceRow++;
        if(sourceRow >= sourceMaxHeight){
            break;
        }
    }

}
























