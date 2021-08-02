#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tgmath.h>

// --- Arithmetic decoding --- 
const char CHAR_A = 'A';
const char CHAR_B = 'B';

void decodeArithmeticSymbol(char symbol, long double * low, long double * high, long double * range, const double rangeA[2], const double rangeB[2]) {
    // Use encoding algorithm found in slide 56 of Lecture 5
    *range = *high - *low;
    if(symbol  == CHAR_A) {
        *high = *low + *range * (rangeA[1]);
        *low = *low + *range * (rangeA[0]);
    }
    else if(symbol == CHAR_B) {
        *high = *low + *range * (rangeB[1]); 
        *low = *low + *range * (rangeB[0]);
    }
}

void arithmeticCoding(std::string fileName) {

    std::ifstream inputFileStream(fileName);

    if(inputFileStream.is_open()) {
        std::string fileInput = "";
        while(!inputFileStream.eof()){

            long double low = 0.0;
            long double high = 1.0;
            long double range = low + high;
            const double rangeA[2] = {0.0, 0.5};
            const double rangeB[2] = {0.5, 1.0};

            std::getline(inputFileStream, fileInput);
            std::cout << "Range to decode: " << fileInput << '\n';

            int codeLength = fileInput.length();

            // Decoding occurs here
            for(int i = 0; i < codeLength; i++) {
                char symbol = fileInput[i];
                std::cout << "Symbol at position " << i << ": " << symbol << '\n';
                decodeArithmeticSymbol(symbol, &low, &high, &range, rangeA, rangeB);
                std::cout << "Range = [" << low << ", " << high << ")\n";
            }
            std::cout << "Final Range:\n" << "Range = [" << low << ", " << high << ")\n";
        }

        inputFileStream.close();
    }

}

// --- Discrete Cosine Transform --- 
std::vector<double> generateIntegerVectorFromString(std::string inputString) {
    int length = inputString.length();
    double num = 0;
    std::vector<double> vectorToReturn;
    for(int i = 0; i < length; i++ ) {
        if(std::isspace(inputString[i])){
           vectorToReturn.push_back(num); 
           num = 0;
        }
        else{
            num = (num * 10) + (inputString[i] - '0');
        }
    } 
    vectorToReturn.push_back(num);   
    return vectorToReturn;
}

std::vector<std::vector<double>> getTranspose(std::vector<std::vector<double>> inputMatrix) {
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

double dctTransform(int i, int j, int n) {
    double a = (i == 0) ? (sqrt((double)1 / n)) : (sqrt((double)2 / n));
    double numerator = ((2 * j  + 1) * i * M_1_PI);
    double denominator = (2 * n);
    return a * cos(numerator / denominator);
}

std::vector<std::vector<double>> transformMatrix(std::vector<std::vector<double>> matrixA, std::vector<std::vector<double>> matrixB, int dimension) {
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

void dct(std::string fileName) {
    std::ifstream inputFileStream(fileName);

    std::vector<std::vector<double>> matrix;
    std::vector<std::vector<double>> transform;
    std::vector<std::vector<double>> transformTranspose;

    if(inputFileStream.is_open()) {
        while(!inputFileStream.eof()) {
            std::string inputString = "";
            std::getline(inputFileStream, inputString);
            
            matrix.push_back(generateIntegerVectorFromString(inputString));
        }
        inputFileStream.close();
    }

    // Get transformation matrices
    int N = matrix[0].capacity();
    for(int i = 0; i < N; i++) {
        std::vector<double> newRow;
        for(int j = 0; j < N; j++) {
            newRow.push_back(dctTransform(i, j, N));
        }
        transform.push_back(newRow);
    }
    transformTranspose = getTranspose(transform);
    std::cout << "Transform Matrix:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << transform[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Transform Matrix Transpose:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << transformTranspose[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Apply transformations
    // -- Column
    std::vector<std::vector<double>> transformationA = transformMatrix(transform, matrix, N);
    // -- Row
    std::vector<std::vector<double>> transformationB = transformMatrix(transformationA, transformTranspose, N);

    std::cout << "Matrix before DCT:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix after DCT:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << (int)transformationB[i][j] << " ";
        }
        std::cout << std::endl;
    }
   
}


int main(int argc, char * argv[]) {
   //arithmeticCoding(argv[1]);
   dct(argv[1]);
    //std::cout << dctTransform(2, 2, 4);
// For testing multiplication
//    std::vector<std::vector<int>> a = {
//        {1, 2, 4, 6},
//        {5, 7, 8, 0},
//        {2, 3, 5, 8},
//        {2, 5, 10, 11}
//    };
//    std::vector<std::vector<int>> b = {
//        {6, 23, 1, 3},
//        {21, 0, 8, 9},
//        {9, 8, 10, 11},
//        {7, 6, 2, 1}
//    };
   
//    std::vector<std::vector<int>> result = transformMatrix(a, b, 4);

//     for(int i = 0; i < 4; i++) {
//         for(int j = 0; j < 4; j++) {
//             std::cout << result[i][j] << " ";
//         }
//         std::cout << "\n";
//     }

}