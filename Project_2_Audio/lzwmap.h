#ifndef LZWMAP_H
#define LZWMAP_H
#include<iostream>
#include <map>
#include <QVector>

class LZWMap
{
public:
    LZWMap(QVector<double> sequence);
    int getSizeInBytes();
    std::map<std::vector<double>, int> dictionary;
    std::vector<int> newCode;
private:
    int getCodeFromMap(std::vector<double> key, int * code);
    void addToMap(std::vector<double> key, int value);
};

#endif // LZWMAP_H
