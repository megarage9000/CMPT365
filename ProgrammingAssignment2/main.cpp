#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include  <tgmath.h> 
#include <vector>

// Huffman Decoding


std::vector<std::vector<char>> getHuffmanDictionary(int numSymbols, std::istream * input) {
    // Creating the dictionary
    std::string fileInput;
    int maxCodeLength = 0;
    int inputLength = 0;
    char symbols[26];
    std::string codes[26];

    for(int i = 0; i < numSymbols; i++) {
        std::getline(*input, fileInput);
        inputLength = fileInput.length();
        symbols[i] = fileInput[0];

        int j = 1;
        while(std::isspace(fileInput[j])){j++;}
        int binaryLength = inputLength - j;
        if(binaryLength > maxCodeLength){
            maxCodeLength = binaryLength;
        }
        codes[i] = fileInput.substr(j, (binaryLength)); 
    }

    int maxNumEntries = pow(2, maxCodeLength);
    std::vector<std::vector<char>> huffmanDec(maxNumEntries, {' ', ' '});

    for(int i = 0; i < numSymbols; i++) {
        int length = codes[i].length();
        int value = std::stoi(codes[i]) << ((maxCodeLength - length) + 1);
        huffmanDec[value][0] = symbols[i];
        huffmanDec[value][1] = '0' + (length - 1);
    }

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

void HuffmanDecoding(std::string filename) {
    std::ifstream input(filename);
    if(input.is_open()) {
        
        std::string fileInput;
        std::string output;
        int outputIndex = 0;


        // Get number of symbols
        std::getline(input, fileInput);
        int numSymbols = std::stoi(fileInput);
        std::cout << numSymbols << std::endl;

        
        std::vector<std::vector<char>> dec = getHuffmanDictionary(numSymbols, &input);


        std::getline(input, fileInput);
        int code = stoi(fileInput);
        std::cout << code << std::endl;
    }
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