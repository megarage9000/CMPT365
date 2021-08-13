#include "lzwmap.h"


// Returns a code given a vector, else it updates the map with a new value
// - if it doesn't find a value, returns -1
int LZWMap::getCodeFromMap(std::string key, int * code) {
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

void LZWMap::addToMap(std::string key, int value){
    dictionary.insert(std::pair<std::string, char> (key, value) );
}

LZWMap::LZWMap() {

}

LZWMap::LZWMap(QVector<int> sequence)
{

    newCode = "";

    // Convert sequence to string
    std::ostringstream oss;
    std::copy(sequence.begin(), sequence.end() - 1,
              std::ostream_iterator<int>(oss, SEPARATOR.c_str()));
    oss << sequence.back();
    std::string sequenceString = oss.str();

    getCodeFromMap(SEPARATOR, &code);
    getCodeFromMap("0", &code);
    getCodeFromMap("1", &code);
    getCodeFromMap("2", &code);
    getCodeFromMap("3", &code);
    getCodeFromMap("4", &code);
    getCodeFromMap("5", &code);
    getCodeFromMap("6", &code);
    getCodeFromMap("7", &code);
    getCodeFromMap("8", &code);
    getCodeFromMap("9", &code);
    getCodeFromMap("-", &code);


    int sequenceLength = sequenceString.length();

    std::string sequenceToRead = std::string(1, sequenceString[0]);
    std::string newSequence = "";
    for(int i = 1 ; i < sequenceLength; i++){
        char nextInputChar = sequenceString[i];

        newSequence = sequenceToRead + nextInputChar;
        int retrievedCode = getCodeFromMap(newSequence, &code);
        // If not exist
        if(retrievedCode == -1){
            newCode += std::to_string(getCodeFromMap(sequenceToRead, &code));
            newSequence = "";
            sequenceToRead = std::string(1, nextInputChar);
        }
        // If exist
        else{
            sequenceToRead = newSequence;
        }
    }
}

void LZWMap::writeToFile(QString filename) {
    QFile file(filename);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Write code
        int newCodeSize = newCode.length();
        for(int i = 0; i < newCodeSize; i++) {
            out << newCode[i];
        }

        file.close();
    }
    else {
        return;
    }
}
