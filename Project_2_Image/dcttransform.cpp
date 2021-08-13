#include "dcttransform.h"



dctTransform::dctTransform(std::vector<std::vector<int>> values, bool inverse)
{
    int width = values[0].size();
    int height = values.size();

    result = std::vector<std::vector<int>>();
    for(int i = 0; i < height; i++){
        result.push_back(std::vector<int>(width, 0));
    }

    // Create Transform matrix
    transform = std::vector<std::vector<double>>();
    for(int i = 0; i < DIMENSION; i++){
        std::vector<double> row = std::vector<double>();
        for(int j = 0; j < DIMENSION; j++){
            double result = getDctTransform(i, j, DIMENSION);
            row.push_back(result);
        }
        transform.push_back(row);
    }
    // Get Transform transpose
    transformTranspose = getTranspose(transform);


    // Determining A and B matrices for multiplication
    std::vector<std::vector<double>> matrixA;
    std::vector<std::vector<double>> matrixB;
    if(inverse){
        matrixA = transformTranspose;
        matrixB = transform;
    }
    else{
        matrixA = transform;
        matrixB = transformTranspose;
    }

    // For DCT, we are doing A x values x B
    int row = 0;
    int col = 0;
    for(; row < height; row += DIMENSION) {
        for(; col < width; col += DIMENSION){
            int rowEnd = (row + DIMENSION) - 1;
            if(rowEnd >= height){
                rowEnd = height - 1;
            }
            int colEnd = (col + DIMENSION) - 1;
            if(colEnd >= width){
                colEnd = width - 1;
            }

            // apply dequantization if inverese
            if(inverse){
                for(int i = row; i < rowEnd; i++) {
                    for(int j = col; j < colEnd; j++) {
                        values[i][j] = (int)values[i][j] * quantTable[i % DIMENSION][j % DIMENSION];
                    }
                }
            }

            // A x values x B
            std::vector<std::vector<double>> subMatrixValues = createSubMatrix(values, row, col, rowEnd, colEnd);
            std::vector<std::vector<double>> resultA = matrixMultiplication(matrixA, subMatrixValues);
            std::vector<std::vector<double>> resultB = matrixMultiplication(resultA, matrixB);
            mapMatrixValues(&result, resultB, row, col, rowEnd, colEnd);

            // apply quantization if not inverse
            if(!inverse){
                for(int i = row; i < rowEnd; i++) {
                    for(int j = col; j < colEnd; j++) {
                        result[i][j] = (int)result[i][j] / quantTable[i % DIMENSION][j % DIMENSION];
                    }
                }
            }

        }
        col = 0;
    }
}

// Returns transpose matrix
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

// Gets the DCT value for a given row and column and dimension
double dctTransform::getDctTransform(int i, int j, int n) {
    double a = (i == 0) ? (sqrt(1.0 / n)) : (sqrt(2.0 / n));
    double numerator = ((2 * j  + 1) * i * M_PI);
    double denominator = (2 * n);
    return a * cos(numerator / denominator);
}


// Matrix multiplication = A x B
std::vector<std::vector<double>> matrixMultiplication(std::vector<std::vector<double>> matrixA, std::vector<std::vector<double>> matrixB){
    int dimension = matrixA[0].size();
    std::vector<std::vector<double>> resultMatrix;
    for(int row = 0; row < dimension; row++) {
        std::vector<double> newRow;
        for(int col = 0; col < dimension; col++) {
            double result = 0;
            for(int k = 0; k < dimension; k++) {
                double aResult = matrixA[row][k];
                double bResult = matrixB[k][col];
                result += (aResult * bResult);
            }
            newRow.push_back(result);
        }
        resultMatrix.push_back(newRow);
    }
    return resultMatrix;
}

// Creates a smaller matrix from a larger matrix
// - Requires a rowStart and rowEnd, colStart and colEnd
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

// Maps matrix values from one matrix to another
void mapMatrixValues(std::vector<std::vector<int>> * dest, std::vector<std::vector<double>> source, int rowStart, int colStart, int rowEnd, int colEnd){

    int sourceMaxWidth = source[0].size();
    int sourceMaxHeight = source.size();

    int sourceRow = 0;
    int sourceCol = 0;

    for(int row = rowStart; row <= rowEnd; row++){

        for(int col = colStart; col <= colEnd; col++){
            dest->at(row)[col] = source[sourceRow][sourceCol];
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
























