#include <iostream>
#include <fstream>
#include <cmath>

#include <vector>

#include "math_tool.h"


int main()
{
    // 文件流
    // std::ofstream outFile;
    // outFile.open("experiment-data/SimilarKeySize.csv", std::ios::app);
    // BIKE参数
    size_t r = 12323;
    size_t d = 71;
    size_t w = 142;
    size_t t = 134;
    // 相似度密钥容量
    // outFile << "BIKE Parameter: " << "r = " << r << " d = " << d << " t = " << t << std::endl;
    /*for(int similar = 3; similar != 40; ++similar)
    {
        outFile << similar << "," << log2(r) + log2Choose(r-d,d-similar) + log2Choose(d,similar) - log2Choose(r, d) << std::endl;
    }
    outFile.close();*/

    // 线性拟合外推
    std::vector<double> DFR9973 = {-11.538,-11.446,-11.314,-11.098,-11.449,-9.469,-8.729,-6.861,-11.512};
    std::vector<double> DFR10007 = {-12.799,-12.648,-12.495,-12.132,-11.597,-10.565,-9.722,-7.665,-12.840};

    for(int i = 0; i != DFR10007.size(); ++i)
    {
        double k = (DFR9973[i]-DFR10007[i])/(9973-10007);
        double b = DFR10007[i] - k*10007;
        std::cout <<  i << ":" << k*r+b << std::endl;
    }

    /*double x1 = 0, y1 = 0;
    double x2 = 0, y2 = 0; 
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    double k = (y1-y2)/(x1-x2);
    double b = y1 - k*x1;
    std::cout << k*r + b << std::endl;*/
 
    return 0;
}