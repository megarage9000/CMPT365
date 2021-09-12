#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>

// --- Arithmetic decoding --- 
const char CHAR_A = 'A';
const char CHAR_B = 'B';
const int MAX_NUM_DECIMALS = 50;

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
            std::cout << std::setprecision(MAX_NUM_DECIMALS);
            std::cout << "############################\n";
            long double low = 0.0;
            long double high = 1.0;
            long double range = low + high;
            const double rangeA[2] = {0.0, 0.5};
            const double rangeB[2] = {0.5, 1.0};

            std::getline(inputFileStream, fileInput);
            std::cout << "Range to decode: " << fileInput << '\n';
            std::cout << "---------------------------\n";

            int codeLength = fileInput.length();

            // Decoding occurs here
            for(int i = 0; i < codeLength; i++) {
                char symbol = fileInput[i];
                //std::cout << "Symbol at position " << i << ": " << symbol << '\n';
                decodeArithmeticSymbol(symbol, &low, &high, &range, rangeA, rangeB);
                //std::cout << "Range = [" << low << ", " << high << ")\n";
            }
            //std::cout << "---------------------------\n";
            std::cout << "Final Range:\n" << "Range = [" << low << ", " << high << ")\n";
            std::cout << "############################\n";
        }

        inputFileStream.close();
    }

}

// --- Discrete Cosine Transform --- 
// Get a vector double from an string of space separated numbers
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

// Transposes a vector double matrix
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

// Returns appropriate dct transform value according to i, j and n
double dctTransform(int i, int j, int n) {
    double a = (i == 0) ? (sqrt(1.0 / n)) : (sqrt(2.0 / n));
    double numerator = ((2 * j  + 1) * i * M_PI);
    double denominator = (2 * n);
    return a * cos(numerator / denominator);
}

// Multiplies 2 vector double matrices, returns a new matrix as a result
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
    else{
        return;
    }
    std::cout << "############################\n";
    int N = matrix[0].size();
    if(N != (int)matrix.size()) {
        std::cout << "Matrix is not square!\n";
        return;
    }
    std::cout<< std::setprecision(4);
    std::cout << "N = " << N << "\n";
    std::cout << "---------------------------\n";
    std::cout << "Matrix before DCT:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Get transformation matrices
    for(int i = 0; i < N; i++) {
        std::vector<double> newRow;
        for(int j = 0; j < N; j++) {
            newRow.push_back(dctTransform(i, j, N));
        }
        transform.push_back(newRow);
    }
    transformTranspose = getTranspose(transform);
    std::cout << "---------------------------\n";
    std::cout << "Transform Matrix:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << transform[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "---------------------------\n";
    std::cout << "Transform Matrix Transpose:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << transformTranspose[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Apply transformations
    // TXT_Transpose (Col -> Row Transform)
    std::vector<std::vector<double>> transformationColRow = transformMatrix(transformMatrix(transform, matrix, N), 
                                                        transformTranspose, N);
    // T_TransposeXT (Row -> Col Transform)
    std::vector<std::vector<double>> transformationRowCol = transformMatrix(transformMatrix(matrix, transformTranspose, N), 
    transform, N);
    std::cout << "---------------------------\n";
    std::cout << "Matrix after DCT (Column transformation -> Row transformation):\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << (int)transformationColRow[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "---------------------------\n";
    std::cout << "Matrix after DCT (Row transformation -> Column transformation):\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << (int)transformationColRow[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "---------------------------\n";
    std::cout << "############################\n";
}


int main(int argc, char * argv[]) {
    // if(argc != 3) {
    //     std::cout << "usage: ./test {Arithmetic Encoding Input Text File} {Discrete Cosine Transformation Input Text File}\n";
    //     return 1;
    // }
    // arithmeticCoding(argv[1]);
    dct(argv[1]);
    return 0;
}