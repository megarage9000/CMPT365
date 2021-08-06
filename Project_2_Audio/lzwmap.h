#ifndef LZWMAP_H
#define LZWMAP_H
#include<iostream>
#include <map>
#include <QVector>

class LZWMap
{
public:
    LZWMap(QVector<float> sequence);
    int getSizeInBytes();
    std::map<std::vector<float>, int> dictionary;
    std::vector<int> newCode;
private:
    int getCodeFromMap(std::vector<float> key, int * code);
    void addToMap(std::vector<float> key, int value);
};

#endif // LZWMAP_H
