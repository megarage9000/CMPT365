#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// --- Arithmetic decoding --- 
const char CHAR_A = 'A';
const char CHAR_B = 'B';

void decodeArithmeticSymbol(char symbol, float * low, float * high, float * range, const float rangeA[2], const float rangeB[2]) {
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

            float low = 0;
            float high = 1;
            float range = low + high;
            const float rangeA[2] = {0.0, 0.5};
            const float rangeB[2] = {0.5, 1.0};

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
std::vector<int> generateIntegerVectorFromString(std::string inputString) {
    int length = inputString.length();
    int num = 0;
    std::vector<int> vectorToReturn;
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

std::vector<std::vector<int>> getTranspose(std::vector<std::vector<int>> inputMatrix) {
    std::vector<std::vector<int>> transpose;

    int rowLength = inputMatrix[0].capacity();
    int colLength = inputMatrix.capacity();

    for(int i = 0; i < colLength; i++) {
        std::vector<int> newRow;
        for(int j = 0; j < rowLength; j++) {
            newRow.push_back(inputMatrix[j][i]);
        }
        transpose.push_back(newRow);
    }
    return transpose;
}

void dct(std::string fileName) {
    std::ifstream inputFileStream(fileName);

    std::vector<std::vector<int>> matrix;

    if(inputFileStream.is_open()) {
        while(!inputFileStream.eof()) {
            std::string inputString = "";
            std::getline(inputFileStream, inputString);
            
            matrix.push_back(generateIntegerVectorFromString(inputString));
        }
        inputFileStream.close();
    }

    int numRows = matrix.capacity();
    for(int i = 0; i < numRows; i++) {
        int colLength = matrix[i].capacity();
        for(int j = 0; j < colLength; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Transpose:\n";
    std::vector<std::vector<int>> transpose = getTranspose(matrix);
    int numRowsT = transpose.capacity();
    for(int i = 0; i < numRowsT; i++) {
        int colLengthT = transpose[i].capacity();
        for(int j = 0; j < colLengthT; j++) {
            std::cout << transpose[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int main(int argc, char * argv[]) {
   // arithmeticCoding(argv[1]);
   dct(argv[1]);
}