#pragma once

#include <data/System.h>

class BitSet
{
    public:
        BitSet();
        BitSet(const BitSet&);
        BitSet(const char *p);
        BitSet(const uint8_t *p, uint64_t bitsize);
        // For BigInt: BEWARE possible implicit conversion from const char* to Integer when calling the constructor
        // For construction from an array of chars, the caller must use ByteSet(const char* str) signature.
        // For construction from value=0, the caller must explicitely use Integer::zero or Integer(0), else, it could
        // lead to ByteSet(const uint8_t *p, uint64_t size) being called.
        BitSet(const Integer& val, uint64_t bitsize);
        BitSet(const string& str_value, const uint64_t bitsize, const uint8_t in_base);
        
        void set(const Integer& val, const uint64_t bitsize);
        void push_back(const Integer& bits_value, const uint64_t bitsize);
        void push_back_ptr(const uint8_t *p, const uint64_t bitsize);
        void push_back(const string& str_value, const uint64_t bitsize, const uint8_t in_base);
        void clear();
        
        const uint64_t bitsize() const { return end_boffset; }

        const BitSet sha256() const;
        const BitSet keccak256() const;
        const BitSet address() const;

        friend ostream& operator<<(ostream& out, const BitSet& v);
        
        operator uint8_t*() { return reinterpret_cast<uint8_t*>(vvalue.data()); }
        operator const unsigned char*() const { return reinterpret_cast<const unsigned char*>(vvalue.data()); }     
        operator const Integer() const { return a2Integer(vvalue.data(), end_boffset); }

        inline bool operator==(const BitSet& b) const { return Integer(*this) == Integer(b); }
        inline bool operator!=(const BitSet& b) const { return Integer(*this) != Integer(b); }
        inline bool operator< (const BitSet& b) const { return Integer(*this) <  Integer(b); }
        inline bool operator> (const BitSet& b) const { return Integer(*this) >  Integer(b); }
        inline bool operator<=(const BitSet& b) const { return Integer(*this) <= Integer(b); }
        inline bool operator>=(const BitSet& b) const { return Integer(*this) >= Integer(b); }

        //Unaligned operators
        const BitSet at(const uint64_t bitoffset, const uint64_t bitsize) const;
        uint8_t as_uint8(uint64_t bofs = 0) const { return Integer(at(bofs, min(bofs+8, end_boffset) - bofs)); }
        uint16_t as_uint16(uint64_t bofs = 0) const { return Integer(at(bofs, min(bofs+16, end_boffset) - bofs)); }
        uint32_t as_uint32(uint64_t bofs = 0) const { return Integer(at(bofs, min(bofs+32,end_boffset) - bofs)); }
        uint64_t as_uint64(uint64_t bofs = 0) const { return Integer(at(bofs, min(bofs+64,end_boffset) - bofs)); }
        Integer as_Integer(uint64_t bofs = 0) const { return Integer(at(bofs, end_boffset - bofs)); }

    protected:
        const Integer a2Integer(const uint8_t *input, const int32_t bitsize) const;

    private:
        uint64_t end_boffset;
        vector<uint8_t> vvalue;
};