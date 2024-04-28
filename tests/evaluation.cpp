#include <iostream>
#include <fstream>
#include <cmath>

#include "math_tool.h"

int main()
{
    // 文件流
    std::ofstream outFile;
    outFile.open("experiment-data/SimilarKeySize.csv", std::ios::app);
    // BIKE参数
    size_t r = 12323;
    size_t d = 71;
    size_t w = 142;
    size_t t = 134;
    // 相似度密钥容量
    outFile << "BIKE Parameter: " << "r = " << r << " d = " << d << " t = " << t << std::endl;
    for(int similar = 3; similar != 40; ++similar)
    {
        outFile << "Similar " << similar << ":" << log2Choose(r-d,d-similar) + log2Choose(d,similar) + log2(r) - log2Choose(r, d) << std::endl;
    }
    outFile.close();
    return 0;
}