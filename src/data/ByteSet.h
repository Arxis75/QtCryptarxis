#pragma once

#include <data/System.h>
#include <data/Tools.h>     //To improve (migrate some Tools functions into ByteSet class)

class ByteSet
{
    public:       
        ByteSet() { vvalue.reserve(32); }
        /// Array Constructor from vector of bytes
        explicit ByteSet(const vector<uint8_t> &v) { vvalue = v; }
        /// Copy constructor
        ByteSet(const ByteSet &b) : vvalue(b.vvalue) {}

        inline void push_front(const ByteSet &b) { vvalue.insert(vvalue.begin(), b.vvalue.begin(), b.vvalue.end()); }
        inline void push_front(uint8_t val) { push_front((ByteSet)vector<uint8_t>({val})); }
        uint8_t pop_front();
        ByteSet pop_front(uint64_t nb_element);

        inline void push_back(const ByteSet &b) { vvalue.insert(vvalue.end(), b.vvalue.begin(), b.vvalue.end()); }
        inline void push_back(uint8_t val) { vvalue.push_back(val); }
        uint8_t pop_back();
        ByteSet pop_back(uint64_t nb_element);     
    
        inline operator vector<uint8_t>() const { return vvalue; }
        uint8_t operator[](uint64_t index) const;

        inline ByteSet at(const uint64_t offset, const uint64_t nb_element) const { return (ByteSet)vector<uint8_t>(vvalue.begin() + offset, vvalue.begin() + offset + nb_element); }

        inline uint64_t byteSize() const { return vvalue.size(); }
        inline void clear() { vvalue.clear(); }

        ByteSet sha256() const;
        ByteSet keccak256() const;

        static ByteSet generateRandom(uint32_t size);

    protected:
        explicit ByteSet(uint64_t resize_bytes) { vvalue.resize(resize_bytes); }
    
    protected:
        vector<uint8_t> vvalue;
};
