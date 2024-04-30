#ifndef _R_TRANSFORM_H_
#define _R_TRANSFORM_H_

#include "types.h"

// 接受字节表示的in数组，同构映射参数d，输出同构映射后的字节表示数组out。
void transformIsomorphism(OUT uint8_t* out, IN uint8_t* in, IN uint32_t d, int byteLength, int bitLength);
// 接受字节表示的in数组，循环移位参数s，输出循环移位后的字节表示数组out。
void transformShift(OUT uint8_t* out, IN uint8_t* in, IN uint32_t s, int byteLength, int bitLength);

#endif //_R_TRANSFORM_H_