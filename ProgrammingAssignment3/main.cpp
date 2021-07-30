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

}

void dct(std::string fileName) {

}


int main(int argc, char * argv[]) {
    arithmeticCoding(argv[1]);
}