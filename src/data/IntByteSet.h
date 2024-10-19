#pragma once

#include <data/ArrayByteSet.h>

class IntByteSet : public ArrayByteSet
{
    public:
        explicit IntByteSet(const Integer &val, uint64_t aligned_size = 0);
        explicit IntByteSet(const ByteSet &val) : ArrayByteSet(val) {};

        inline operator bool() const { return uint8_t(*this) ? true : false; };
        inline operator uint8_t() const { return right(1); }
        inline operator uint16_t() const { return right(2); }
        inline operator uint32_t() const { return right(4); }
        inline operator uint64_t() const { return right(8); }
        inline operator Integer() const { return right(byteSize()); }

        friend ostream& operator<<(ostream &out, const IntByteSet &val);
private:
        Integer right(uint64_t size) const;
};