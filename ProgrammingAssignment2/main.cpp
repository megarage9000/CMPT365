#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include  <tgmath.h> 
#include <vector>

// --- Huffman Decoding --- 
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
        int binaryLength = inputLength - j;
        if(binaryLength > *maxCodeLength){
            *maxCodeLength = binaryLength;
        }
        codes[i] = fileInput.substr(j, (binaryLength)); 
    }



    // Creating the dictionary and setting the boundaries per symbol,
    // using vector for simplicity
    int maxNumEntries = pow(2, *maxCodeLength);
    std::vector<std::vector<char>> huffmanDec(maxNumEntries, {' ', ' '});

    for(int i = 0; i < numSymbols; i++) {
        int length = codes[i].length();
        long value = std::stoi(codes[i], nullptr, 2); 
        value = value << (*maxCodeLength - length);
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

    return huffmanDec;
}

int readBitsFromSubstr(std::string binaryString, int * startIndex, int length) {
    int binaryStringLength = (int)binaryString.length();
    if(*startIndex >= binaryStringLength) {
        return -1;
    }
    else {
        std::string substring = binaryString.substr(*startIndex, length);
        int substringLength = substring.length();
        *startIndex += substringLength;
        if(substringLength < length) {
            // Right shifting so it returns the right amount of bits (padding)
            return std::stoi(substring, nullptr, 2) << ((length - substringLength));
        }
        else {
            return std::stoi(substring, nullptr, 2);
        }
    }
}

int HuffmanDecoding(std::string filename) {
    std::ifstream input(filename);
    if(input.is_open()) {
        while(!input.eof()) {
            std::string fileInput = "";
            std::string output = "";

            // Get number of symbols
            std::getline(input, fileInput);
            int numSymbols = std::stoi(fileInput);

            // Generate table
            int maxCodeLength = 0;
            std::vector<std::vector<char>> dec = getHuffmanDictionary(numSymbols, &input, &maxCodeLength);
            
            // Getting the code, we use string for dynamic size, as storing in ints / longs
            // are of fixed size
            std::getline(input, fileInput);
            
            // Determining rejection bit
            int rejectionBit = ~(-1 << maxCodeLength);

            // Decoding the code
            int fileInputIndex = 0;
            int tableValue = readBitsFromSubstr(fileInput, &fileInputIndex, maxCodeLength);
            do {
                output += dec[tableValue][0];
                int bitLength = dec[tableValue][1] - '0';
                tableValue = tableValue << bitLength;
                int newBits = readBitsFromSubstr(fileInput, &fileInputIndex, bitLength);

                // if EOF, check for remaining bits if they are readable
                if(newBits == -1) { 
                    tableValue = tableValue & rejectionBit;
                    if(tableValue < (int)dec.size()){
                        int length = dec[tableValue][1] - '0';
                        if(length == bitLength) {
                            output += dec[tableValue][0];
                        }
                    }
                    break;
                } else{
                    tableValue = tableValue | newBits;
                    tableValue = tableValue & rejectionBit;
                }
            } while(true);  
            std::cout << "-----------------\n";
            std::cout << "Sequence = " << output << std::endl;
            std::cout << "-----------------\n";
        }
        input.close();
    }
    else{
        return -1;
    }
    return 0;
}

// --- LZW Encoding --- //

std::vector<std::string> generateDictionary (int numSymbols, std::ifstream *input) {

    std::vector<std::string> LZWDict;
    std::string fileInput;
    for(int i = 0; i < numSymbols; i++) {
        std::getline(*input, fileInput);
        int length = fileInput.length();
        int j = 1;
        while(std::isspace(fileInput[j])){++j;}
        int size = length - j;
        LZWDict.push_back(fileInput.substr(j, size));
    }
    return LZWDict;
}

int LZWDecoding(std::string fileName) {
    std::ifstream input(fileName);
    if(input.is_open()) {
        while(!input.eof()) {
            // Declaring data
            std::string fileInput;
            std::string code;
            int numSymbols;
            std::vector<std::string> dict;

            // Getting symbols to decode
            std::getline(input, fileInput);
            code = fileInput;

            // Getting number of symbols in present dictionary
            std::getline(input, fileInput);
            numSymbols = stoi(fileInput, nullptr, 10);

            dict = generateDictionary(numSymbols, &input);

            // Decoding symbols
            std::string output = "";
            std::string inputCharacters(1, code[0]);
            int index = 1;
            int maxLength = (int)code.length();

            while(index < maxLength) {
                char nextChar = code[index];
                std::string combination = inputCharacters;
                combination += nextChar;
                // if s + c exist
                if(std::find(dict.begin(), dict.end(), combination) != dict.end()) {
                    // s = s + c
                    inputCharacters += nextChar;
                }
                else{
                    // output s
                    auto match = std::find(dict.begin(), dict.end(), inputCharacters);
                    int i = match - dict.begin();
                    output += std::to_string(i);
                    // add s + c to dictionary
                    dict.push_back(combination);
                    // s = c
                    inputCharacters = std::string(1, nextChar);
                }
                index++;
            }
            // output s
            auto match = std::find(dict.begin(), dict.end(), inputCharacters);
            int i = match - dict.begin();
            output += std::to_string(i);

            std::cout << "-----------------\n";
            std::cout << "Sequence = " << output << std::endl;
            std::cout << "Final Dictionary\n";
            for(int i = 0; i < (int)dict.size(); i++) {
                std::cout << i << ": " << dict[i] << std::endl;
            }
            std::cout << "-----------------\n";
        }
        input.close();
    }
    else{
        return -1;
    }
    return 0;
}


int main(int argc, char * argv[]) {
    if(argc < 3) {
        std::cout << "Usage: ./test [huffman Input text file] [LZW Input text file]\n";
        return -1;
    }
    HuffmanDecoding(argv[1]);
    LZWDecoding(argv[2]);
}