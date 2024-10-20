#pragma once

#include <data/IntByteSet.h>

class DecStrByteSet : public IntByteSet
{
    public:
        DecStrByteSet() : IntByteSet() {}
        /// @brief Constructor from a presumably Hex string value
        /// @param val Hex string
        /// @param aligned_size either a total byte-size required for 0-padding
        /// or 0 let the constructor apply a simple byte-padding and guess the underlying value size.
        explicit DecStrByteSet(const string &val, uint64_t aligned_size = 0);
        /// @brief Constructor from the underlying ByteSet
        /// @param val 
        explicit DecStrByteSet(const ByteSet &val) : IntByteSet(val) { }

        /// @brief string operator returning the default representation
        /// @return Size in Bytes of the value represented by the hex/bin strings, 0-padding included.
        /// The dec/Gwei strings being not aligned, their size is not relevant here
        operator string() const;
};