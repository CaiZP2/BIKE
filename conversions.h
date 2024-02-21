/******************************************************************************
 * BIKE -- Bit Flipping Key Encapsulation
 *
 * Copyright (c) 2021 Nir Drucker, Shay Gueron, Rafael Misoczki, Tobias Oder,
 * Tim Gueneysu, Jan Richter-Brockmann.
 * Contact: drucker.nir@gmail.com, shay.gueron@gmail.com,
 * rafaelmisoczki@google.com, tobias.oder@rub.de, tim.gueneysu@rub.de,
 * jan.richter-brockmann@rub.de.
 * 
 * Permission to use this code for BIKE is granted.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * The names of the contributors may not be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ""AS IS"" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS CORPORATION OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/


#ifndef _R_CONVERSIONS_H_
#define _R_CONVERSIONS_H_

#include <vector>

// 接受二进制表示的in数组,，将其转为字节表示的out数组，length为二进制表示的数组长度
// in的length与out的length服从关系：out.length = ceil(in.length/8) 向上取整
// 例：in = {0,1,0,1,1,0,0,0,1,0,1,0}，in.length = 12, length = in.length（in为二进制表示） 
// 函数结果 out = {00011010,(0000)0101}（8个二进制位合并且逆向表达）
// ！！注：out中第二个元素的0000部分的结果依赖于传入的out数组的原始值，函数并不会对这一超过length的部分做处理
int convertBinaryToByte(uint8_t* out, const uint8_t* in, uint32_t length);
// 接受字节表示的in数组，将其转为二进制表示的out数组，length为二进制表示的数组长度
// 可以认为是上面函数的反函数
int convertByteToBinary(uint8_t* out, const uint8_t* in, uint32_t length);
// 接受字节表示的in数组，将其转为压缩(compact)形式（只存取向量中1的位置信息）
// 例：in = {00011010,(0000)0101} (二进制表示为{0,1,0,1,1,0,0,0,1,0,1,0})
// 结果 out = {1,3,4,8,10}
void convert2compact(OUT uint32_t out[DV], IN const uint8_t in[R_SIZE]);
// 接受字节表示的in数组，输出其1的位置信息out
// 相比上述函数，采用vector实现，支持更加灵活的向量长度与1的个数
void convert2compact_flex(OUT std::vector<uint32_t> &out, IN const uint8_t *in, IN uint32_t byteLength, IN uint32_t bitLength);

#endif //_R_CONVERSIONS_H_

