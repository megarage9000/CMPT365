#include "lzwmap.h"


// Returns a code given a vector, else it updates the map with a new value
// - if it doesn't find a value, returns -1
int LZWMap::getCodeFromMap(std::vector<double> key, int * code) {
    auto element = dictionary.find(key);
    if(element != dictionary.end()) {
        return element->second;
    }
    else{
        addToMap(key, *code);
        (*code)++;
        return -1;
    }
}

void LZWMap::addToMap(std::vector<double> key, int value){
    dictionary.insert(std::pair<std::vector<double>, int> (key, value) );
}

LZWMap::LZWMap(QVector<double> sequence)
{
    int numElements = sequence.size();
    newCode = std::vector<int>();

    // initialize dictionary with 3 values of sequences
    addToMap(std::vector<double>{sequence[0]}, 0);
    addToMap(std::vector<double>{sequence[1]}, 1);
    addToMap(std::vector<double>{sequence[2]}, 2);
    int code = 3;

    std::vector<double> sequenceToBeRead = std::vector<double>{sequence[0]};
    for(int i = 1; i < numElements; i++) {
        std::vector<double> prevSequenceRead = std::vector<double>(sequenceToBeRead);
        sequenceToBeRead.push_back(sequence[i]);
        if(getCodeFromMap(sequenceToBeRead, &code) == -1) {
            while(getCodeFromMap(prevSequenceRead, &code) == -1);
            int codeToAdd = dictionary.at(prevSequenceRead);
            newCode.push_back(codeToAdd);
            sequenceToBeRead.clear();
            sequenceToBeRead.push_back(sequence[i]);
        }
    }
    newCode.push_back(
           getCodeFromMap(sequenceToBeRead, &code)
    );

    newCode.shrink_to_fit();
//    int newCodeSize = newCode.size();
//    for(int i = 0; i < newCodeSize; i++) {
//        std::cout << newCode[i];
//    }
//    std::cout << "\n";
    sequence.shrink_to_fit();

    std::cout << "Original sequence size = " << (int)sequence.size() << ", Coded sequence size = " << (int)newCode.size()<< "\n";
}

