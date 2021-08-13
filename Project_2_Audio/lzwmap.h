#ifndef LZWMAP_H
#define LZWMAP_H

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <map>
#include <iostream>
#include <QVector>
#include <QFile>
#include <QTextStream>

const std::string SEPARATOR = "|";

class LZWMap
{
public:
    LZWMap();
    LZWMap(QVector<int> sequence);
    int getSizeInBytes();
    std::map<std::string, int> dictionary;
    std::string newCode;
    void writeToFile(QString filename);
private:
    int code = 0;
    int getCodeFromMap(std::string key, int * code);
    void addToMap(std::string key, int value);
};

#endif // LZWMAP_H
