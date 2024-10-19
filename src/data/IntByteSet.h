#pragma once

#include <data/ArrayByteSet.h>

class IntByteSet : public ArrayByteSet
{
    public:
        explicit IntByteSet(const Integer &val, uint64_t aligned_size = 0);
        explicit IntByteSet(const ByteSet &val) : ArrayByteSet(val) {};

        /*inline const uint8_t as_uint8() const { return (byteSize()>0 ? vvalue[0] : 0); }
        const uint64_t as_uint64() const;
        const Integer as_Integer() const { return a2Integer(vvalue.data(), vvalue.size()); }
        const bool as_bool() const { return (as_uint8() ? true : false); }*/

        inline operator bool() const { return uint8_t(*this) ? true : false; };
        inline operator uint8_t() const { return right(1); }
        inline operator uint16_t() const { return right(2); }
        inline operator uint32_t() const { return right(4); }
        inline operator uint64_t() const { return right(8); }
        inline operator Integer() const { return right(byteSize()); }

        inline void push_front(const Integer &val, uint64_t aligned_size = 0) { ByteSet::push_front(IntByteSet(val, aligned_size)); }
        inline void push_back(const Integer &val, uint64_t aligned_size = 0) { ByteSet::push_back(IntByteSet(val, aligned_size)); }

        friend ostream& operator<<(ostream &out, const IntByteSet &val);
private:
        Integer right(uint64_t size) const;
};