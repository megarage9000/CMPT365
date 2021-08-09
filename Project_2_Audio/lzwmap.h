#ifndef LZWMAP_H
#define LZWMAP_H
#include<iostream>
#include <map>
#include <QVector>
#include <QFile>
#include <QTextStream>

class LZWMap
{
public:
    LZWMap();
    LZWMap(QVector<int> sequence);
    int getSizeInBytes();
    std::map<std::vector<int>, int> dictionary;
    std::vector<int> newCode;
    void writeToFile(QString filename);
private:
    int getCodeFromMap(std::vector<int> key, int * code);
    void addToMap(std::vector<int> key, int value);
};

#endif // LZWMAP_H
