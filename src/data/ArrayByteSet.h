#pragma once

#include <data/ByteSet.h>

class ArrayByteSet : public ByteSet
{
    public:
        ArrayByteSet(const uint8_t *p, uint64_t aligned_size);
        explicit ArrayByteSet(const char* str) : ArrayByteSet(reinterpret_cast<const uint8_t*>(str), strlen(str)) {}
        explicit ArrayByteSet(const ByteSet &val) : ByteSet(val) {}

        inline operator uint8_t*() { return reinterpret_cast<uint8_t*>(vvalue.data()); }
        inline operator const unsigned char*() const { return reinterpret_cast<const unsigned char*>(vvalue.data()); } 
        
        inline void push_front(const uint8_t *p, const uint64_t aligned_size) { ByteSet::push_front(ArrayByteSet(p, aligned_size)); }
        inline void push_back(const uint8_t *p, const uint64_t aligned_size) { ByteSet::push_back(ArrayByteSet(p, aligned_size)); }

        inline void push_front(const char* str) { ByteSet::push_front(ArrayByteSet(str)); }
        inline void push_back(const char* str) { ByteSet::push_back(ArrayByteSet(str)); }
};