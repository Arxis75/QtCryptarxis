#include "IntByteSet.h"

#include <data/Tools.h>

IntByteSet::IntByteSet(const Integer &val, uint64_t aligned_size)
    : ArrayByteSet("")
{
    uint64_t value_size = val.size_in_base(256);
    uint64_t extra_size = (aligned_size > value_size ? aligned_size - value_size : 0);
    for(int i=0;i<extra_size;i++)
        vvalue.push_back(0x00);
    for(int i=0;i<value_size;i++)
        vvalue.push_back(0xFF & uint8_t(val>>((value_size-1-i)<<3)));
}

Integer IntByteSet::right(uint64_t size) const
{
    Integer ret_value = 0;
    for(int i=0;i<min((uint64_t)size, byteSize());i++)
        ret_value += (vvalue[byteSize()-1-i] << (i<<4));
    return ret_value;     
}

ostream& operator<< (ostream& out, const IntByteSet &val) {
    out << hex << Integer(val);
    return out;
}
