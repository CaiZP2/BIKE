#ifndef MATH_TOOL_H
#define MATH_TOOL_H

#include "types.h"

// 阶乘对数函数
// 接受非负整数n 返回log2(n!)
double log2Gamma(size_t n);

// 组合数对数函数
// 接受非负整数n k，返回log2(C(n,k))
double log2Choose(size_t n, size_t k);
double xlog2y(double x, double y);

// 伯努利分布对数函数
// log2( C(n,k) p^k q^{n-k} )
double log2Binomial(size_t n, size_t k, double p, double q);

#endif