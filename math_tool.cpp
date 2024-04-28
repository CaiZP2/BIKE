#include <cmath>
#include "math_tool.h"

double log2Gamma(size_t n)
{
    if(n == 0 || n == 1)
    {
        return 0.0;
    } else {
        double result = 0.0;
        while(n != 0) {
            result += log2(n);
            --n;
        }
        return result;
    }
}

double log2Choose(size_t n, size_t k)
{
    if ((k == 0) || (n == k)){
        return 0.0;
    }
    else{
        return log2Gamma(n) - log2Gamma(k) - log2Gamma(n - k);
    }
}

double xlog2y(double x, double y)
{
    if(x == 0.0)
    {
        return 0.0;
    } else {
        return x * log2(y);
    }
}

double log2Binomial(size_t n, size_t k, double p, double q)
{
    return log2Choose(n,k) + xlog2y(k, p) + xlog2y(n-k, q);
}