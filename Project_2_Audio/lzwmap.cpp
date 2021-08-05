#include "lzwmap.h"


LZWMap::LZWMap(QVector<double> sequence)
{
    int numElements = sequence.size();
    newCode = std::vector<int>();

    // initialize dictionary with 3 values of sequences
    dictionary[std::vector<double> {sequence[0]}] = 0;
    dictionary[std::vector<double> {sequence[1]}] = 1;
    dictionary[std::vector<double> {sequence[2]}] = 2;
    int code = 3;

    std::vector<double> sequenceToBeRead = std::vector<double>{sequence[2]};

    for(int i = 3; i < numElements; i++) {
        sequenceToBeRead.push_back(sequence[i]);
        // If sequence is not found
        if(dictionary.find(sequenceToBeRead) == dictionary.end()) {
            newCode.push_back(
                        dictionary.find(std::vector<double>(sequenceToBeRead.begin(), sequenceToBeRead.end()- 1))->second
                        );

            dictionary[sequenceToBeRead] = code;
            sequenceToBeRead.clear();
            sequenceToBeRead.push_back(sequence[i]);
            code++;
        }
    }
    newCode.push_back(
            dictionary.find(std::vector<double>(sequenceToBeRead.begin(), sequenceToBeRead.end()))->second
    );

    newCode.shrink_to_fit();
//    int newCodeSize = newCode.size();
//    for(int i = 0; i < newCodeSize; i++) {
//        std::cout << newCode[i];
//    }
//    std::cout << "\n";
    sequence.shrink_to_fit();

    std::cout << "Original sequence size = " << (int)sequence.size() * sizeof(double) << ", Coded sequence size = " << (int)newCode.size() * sizeof(int) << "\n";
}
