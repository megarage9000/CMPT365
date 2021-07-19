#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include  <tgmath.h> 
#include <vector>

// Huffman Decoding
std::vector<std::vector<char>> getHuffmanDictionary(int numSymbols, std::istream * input, int * maxCodeLength) {
    std::string fileInput;
    int inputLength = 0;

    // Searching largest codelength as well as
    // gathering symbols and their respective codes
    char symbols[26];
    std::string codes[26];
    for(int i = 0; i < numSymbols; i++) {
        std::getline(*input, fileInput);
        inputLength = (int)fileInput.length();
        symbols[i] = fileInput[0];

        int j = 1;
        while(std::isspace(fileInput[j])){j++;}
        int binaryLength = inputLength - j - 1;
        if(binaryLength > *maxCodeLength){
            *maxCodeLength = binaryLength;
        }
        codes[i] = fileInput.substr(j, (binaryLength)); 
        std::cout << symbols[i] << ": " << codes[i] << std::endl;
    }

    std::cout << "Max code length = " << *maxCodeLength << std::endl;


    // Creating the dictionary and setting the boundaries per symbol
    int maxNumEntries = pow(2, *maxCodeLength);
    std::vector<std::vector<char>> huffmanDec(maxNumEntries, {' ', ' '});

    for(int i = 0; i < numSymbols; i++) {
        int length = codes[i].length();
        long value = std::stoi(codes[i], nullptr, 2); 
        value = value << (*maxCodeLength - length);
        std::cout << codes[i] << ": " << value << std::endl;
        huffmanDec[value][0] = symbols[i];
        huffmanDec[value][1] = '0' + (length);
    }

    // Filling the values in between the boundaries
    char initialSymbol = huffmanDec[0][0];
    char initialLength = huffmanDec[0][1];
    for(int i = 0; i < maxNumEntries; i++) {
        if(huffmanDec[i][0] == huffmanDec[i][1] && huffmanDec[i][1] == ' '){
            huffmanDec[i][0] = initialSymbol;
            huffmanDec[i][1] = initialLength;
        }
        else{
            initialSymbol = huffmanDec[i][0];
            initialLength = huffmanDec[i][1];
        }
    }

    for(int i = 0; i < maxNumEntries; i++){
        std::cout << i << ": (" << huffmanDec[i][0] << ", " << huffmanDec[i][1] << ")\n"; 
    }

    return huffmanDec;
}

int readBitsFromSubstr(std::string binaryString, int startIndex, int length, int * newIndex) {
    int binaryStringLength = (int)binaryString.length();
    if(startIndex >= binaryStringLength) {
        return -1;
    }
    else {
        std::string substring = binaryString.substr(startIndex, length);
        int substringLength = (int)substring.length();
        *newIndex += substringLength;
        if(substringLength < length) {
            // Right shifting so it returns the right amount of bits
            return std::stoi(substring, nullptr, 2) << (length - substringLength);

        }
        else {
            return std::stoi(substring, nullptr, 2);
        }
    }
}

int HuffmanDecoding(std::string filename) {
    std::ifstream input(filename);
    if(input.is_open()) {
        
        std::string fileInput;
        std::string output = "";


        // Get number of symbols
        std::getline(input, fileInput);
        int numSymbols = std::stoi(fileInput);
        std::cout << numSymbols << std::endl;

        int maxCodeLength = 0;
        std::vector<std::vector<char>> dec = getHuffmanDictionary(numSymbols, &input, &maxCodeLength);
        
        std::getline(input, fileInput);
        std::cout << fileInput;
        std::cout << ": length = " << (int)fileInput.length() << std::endl;
        std::cout << "Max code length = " << maxCodeLength << std::endl;
        
        int rejectionBit = ~(-1 << maxCodeLength);
        std::cout << "rejection bit = " << rejectionBit << std::endl;

        int fileInputIndex = 0;
        int tableValue = readBitsFromSubstr(fileInput, 0, maxCodeLength, &fileInputIndex);
        int outputIndex = 0;
        do {
            output += dec[tableValue][0];
            int bitLength = dec[tableValue][1] - '0';
            std::cout << "Current string = " << output << ", last used table value = " << tableValue <<
            ", bit length = " << bitLength << ", index = " << fileInputIndex << std::endl;
            int newBits = readBitsFromSubstr(fileInput, fileInputIndex, bitLength, &fileInputIndex);
            if(newBits == -1) {
                break;
            }
            tableValue = tableValue << bitLength;
            std::cout << "tableValue = " << tableValue << std::endl;
            tableValue |= newBits;
            std::cout << "tableValue = " << tableValue << std::endl;
            tableValue = tableValue & rejectionBit;
            std::cout << "tableValue = " << tableValue << std::endl;
        } while(true);
 
        std::cout << output << std::endl;
    }

    return -1;
}




int main(int argc, char * argv[]) {
    using namespace std;
    // if(argc != 2) {
    //     cout << "Usage: ./test [filename]\n"; 
    // }
    // else {
    //     string line;
    //     ifstream inputFile(argv[1]);
    //     if(inputFile.is_open()) {
    //         while(getline(inputFile, line)) {
    //             cout << line << endl;
    //         }
    //     }
    //     else {
    //         cout << "Unable to open file\n";
    //     }
    // }
    HuffmanDecoding(argv[1]);
}