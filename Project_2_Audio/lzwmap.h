#ifndef LZWMAP_H
#define LZWMAP_H
#include<iostream>
#include <map>
#include <QVector>

class LZWMap
{
public:
    LZWMap(QVector<double> sequence);
    std::map<std::vector<double>, int> dictionary;
    std::vector<int> newCode;
};

#endif // LZWMAP_H
