#pragma once

#include <data/RawStrByteSet.h>

class ArrayByteSet : public RawStrByteSet
{
    public:
        ArrayByteSet() : RawStrByteSet() {}
        ArrayByteSet(const uint8_t *p, uint64_t aligned_size);
        explicit ArrayByteSet(const char* str) : ArrayByteSet(reinterpret_cast<const uint8_t*>(str), strlen(str)) {}
        explicit ArrayByteSet(const ByteSet &val) : RawStrByteSet(val) {}

        inline operator uint8_t*() { return reinterpret_cast<uint8_t*>(vvalue.data()); }
        inline operator const unsigned char*() const { return reinterpret_cast<const unsigned char*>(vvalue.data()); } 

        inline void push_front(const uint8_t *p, uint64_t aligned_size) { ByteSet::push_front(ArrayByteSet(p, aligned_size)); }
        inline ArrayByteSet pop_front(uint64_t nb_element) { ArrayByteSet(ByteSet::pop_front(nb_element)); }

        inline void push_back(const uint8_t *p, uint64_t aligned_size) { ByteSet::push_back(ArrayByteSet(p, aligned_size)); }
        inline ArrayByteSet pop_back(uint64_t nb_element) { ArrayByteSet(ByteSet::pop_back(nb_element)); }
};