#include "conversions.h"
#include "transform.h"

void transformIsomorphism(uint8_t* out, uint8_t* in, uint32_t d, int byteLength, int bitLength)
{
    std::vector<uint32_t> in_compact;
    convert2compact_flex(in_compact, in, byteLength, bitLength);
    for(int i = 0; i!=in_compact.size(); ++i)
    {
        if(in_compact[i]*d >= bitLength)
        {
            in_compact[i] = (in_compact[i]*d)%(bitLength);
        } else {
            in_compact[i] = (in_compact[i])*d;
        }
    }
    convertCompact2Byte(out,in_compact);
}

void transformShift(uint8_t* out, uint8_t* in, uint32_t s, int byteLength, int bitLength)
{
    std::vector<uint32_t> in_compact;
    convert2compact_flex(in_compact, in, byteLength, bitLength);
    for(int i = 0; i!=in_compact.size(); ++i)
    {
        if((in_compact[i]+s) >= bitLength) 
        {
            in_compact[i] = (in_compact[i]+s)%(bitLength);
        } else {
            in_compact[i] = in_compact[i]+s;
        }
    }
    convertCompact2Byte(out,in_compact);
}