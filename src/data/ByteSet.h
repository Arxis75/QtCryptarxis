#pragma once

#include <data/System.h>

class ByteSet
{
    public:       
        ByteSet() { vvalue.reserve(32); }
        /// Constructor from vector of bytes
        explicit ByteSet(const vector<uint8_t>& v) { vvalue = v; }

        inline void push_front(uint8_t val) { push_front((ByteSet)vector<uint8_t>({val})); }
        inline void push_back(uint8_t val) { vvalue.push_back(val); }
        uint8_t pop_front();
        uint8_t pop_back();

        inline void push_front(const ByteSet &b) { vvalue.insert(vvalue.begin(), b.vvalue.begin(), b.vvalue.end()); }
        inline void push_back(const ByteSet &b) { vvalue.insert(vvalue.end(), b.vvalue.begin(), b.vvalue.end()); }
        ByteSet pop_front(uint64_t nb_element);
        ByteSet pop_back(uint64_t nb_element);
    
        inline bool operator==(const ByteSet &b) const { return vvalue == b.vvalue; };
        inline bool operator!=(const ByteSet &b) const { return !(vvalue == b.vvalue); };
        inline operator vector<uint8_t>() const { return vvalue; }
        inline uint8_t operator[](uint64_t index) const { return vvalue[index]; };

        virtual operator string() const;
        friend ostream& operator<<(ostream& out, const ByteSet& v);

        inline ByteSet at(const uint64_t offset, const uint64_t nb_element) const { return (ByteSet)vector<uint8_t>(vvalue.begin() + offset, vvalue.begin() + offset + nb_element); }

        virtual inline uint64_t byteSize() const { return vvalue.size(); }
        inline void clear() { vvalue.clear(); }

        virtual ByteSet sha256() const;
        virtual ByteSet keccak256() const;

        static ByteSet generateRandom(uint32_t byte_size);

    protected:
        explicit ByteSet(uint64_t resize_bytes) { vvalue.resize(resize_bytes); }
    
    protected:
        //Choice of a protected vector:
        // - protected so RLPByteSet, ArrayByteSet etc... are able to access the data as a pointer
        // - vector and not deque because only vector ensures underlying data contiguous
        vector<uint8_t> vvalue;
};


class BitSet : public ByteSet
{
    public:
        BitSet() : ByteSet() {}

        inline void push_front(uint8_t val) { assert(val==0||val==1); ByteSet::push_front((ByteSet)vector<uint8_t>({val})); }
        inline void push_back(uint8_t val) { assert(val==0||val==1); ByteSet::push_front((ByteSet)vector<uint8_t>({val})); }
        inline uint8_t pop_front() { assert(bitSize()); return ByteSet::pop_front(); }
        inline uint8_t pop_back() { assert(bitSize()); return ByteSet::pop_back(); }

        inline void push_front(const BitSet &b) { vvalue.insert(vvalue.begin(), b.vvalue.begin(), b.vvalue.end()); }
        inline void push_back(const BitSet &b) { vvalue.insert(vvalue.end(), b.vvalue.begin(), b.vvalue.end()); }
        BitSet pop_front(uint64_t nb_element);
        BitSet pop_back(uint64_t nb_element);

        virtual operator string() const;

        inline uint64_t bitSize() const { return vvalue.size(); }

        inline virtual ByteSet sha256() const { return toByteSet().sha256(); }
        inline virtual ByteSet keccak256() const { return toByteSet().keccak256(); }

        ByteSet toByteSet() const;
};