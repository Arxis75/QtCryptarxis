#pragma once

#include <data/ArrayByteSet.h>

class IntByteSet : public ArrayByteSet
{
    public:
        IntByteSet() : ArrayByteSet() {}
        explicit IntByteSet(const Integer &val, uint64_t aligned_size = 0);
        explicit IntByteSet(const ByteSet &val) : ArrayByteSet(val) {}

        /*inline operator bool() const { return uint64_t(*this) ? true : false; };
        inline operator uint8_t() const { return right(1); }
        inline operator uint16_t() const { return right(2); }
        inline operator uint32_t() const { return right(4); }*/
        inline operator uint64_t() const { return right(8); }
        inline operator Integer() const { return right(byteSize()); }

        inline void push_front(const Integer &val, uint64_t aligned_size = 0) { ByteSet::push_front(IntByteSet(val, aligned_size)); }
        inline IntByteSet pop_front(uint64_t nb_element) { return IntByteSet(ByteSet::pop_front(nb_element)); }

        inline void push_back(const Integer &val, uint64_t aligned_size = 0) { ByteSet::push_back(IntByteSet(val, aligned_size)); }
        inline IntByteSet pop_back(uint64_t nb_element) { return IntByteSet(ByteSet::pop_back(nb_element)); }

        inline bool operator>=(const IntByteSet &b) const { return Integer(*this) >= Integer(b); };
        inline bool operator>(const IntByteSet &b) const { return Integer(*this) > Integer(b); };
        inline bool operator<=(const IntByteSet &b) const { return Integer(*this) <= Integer(b); };
        inline bool operator<(const IntByteSet &b) const { return Integer(*this) < Integer(b); };

        inline IntByteSet at(const uint64_t offset, const uint64_t nb_element) const { return (IntByteSet)(ByteSet)vector<uint8_t>(vvalue.begin() + offset, vvalue.begin() + offset + nb_element); }

private:  
        Integer right(uint64_t size) const;
};