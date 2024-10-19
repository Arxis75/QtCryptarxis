#pragma once

#include <data/IntByteSet.h>

class BinStrByteSet : public IntByteSet
{
    public:
        /// @brief Constructor from a presumably Binary string value
        /// @param val Hex string
        /// @param aligned_size either a total byte-size required for 0-padding
        /// or 0 let the constructor apply a simple byte-padding and guess the underlying value size.
        explicit BinStrByteSet(const string &val, uint64_t aligned_size = 0);
        /// @brief Constructor from the underlying ByteSet
        /// @param val 
        explicit BinStrByteSet(const ByteSet &val) : IntByteSet(val) { }

        /// @brief string operator returning the default representation
        /// @return Size in Bytes of the value represented by the hex/bin strings, 0-padding included.
        /// The dec/Gwei strings being not aligned, their size is not relevant here
        operator string() const;

        inline void push_front(const string &val, uint64_t aligned_size = 0) { ByteSet::push_front(BinStrByteSet(val, aligned_size)); }
        inline void push_back(const string &val, uint64_t aligned_size = 0) { ByteSet::push_back(BinStrByteSet(val, aligned_size)); }

    private:
        string removeBaseHeader(const string &val);
        string alignToByte(const string &val, uint64_t aligned_size) const;
        uint8_t charToNibble(const char &c) const;
        char nibbleToChar(const uint8_t &nibble) const;
};