#pragma once

#include <data/IntByteSet.h>

class HexStrByteSet : public IntByteSet
{
    public:
        HexStrByteSet() : IntByteSet() {}
        /// @brief Constructor from a presumably Hex string value
        /// @param val Hex string
        /// @param aligned_size either a total byte-size required for 0-padding
        /// or 0 let the constructor apply a simple byte-padding and guess the underlying value size.
        explicit HexStrByteSet(const string &val, uint64_t aligned_size = 0);
        /// @brief Constructor from the underlying ByteSet
        /// @param val 
        explicit HexStrByteSet(const ByteSet &val) : IntByteSet(val) { }

        /// @brief string operator returning the default representation
        /// @return Size in Bytes of the value represented by the hex/bin strings, 0-padding included.
        /// The dec/Gwei strings being not aligned, their size is not relevant here
        //operator string() const;

        inline void push_front(const string &val, uint64_t aligned_size = 0) { ByteSet::push_front(HexStrByteSet(val, aligned_size)); }
        inline HexStrByteSet pop_front(uint64_t nb_element) { return HexStrByteSet(ByteSet::pop_front(nb_element)); }

        inline void push_back(const string &val, uint64_t aligned_size = 0) { ByteSet::push_back(HexStrByteSet(val, aligned_size)); }
        inline HexStrByteSet pop_back(uint64_t nb_element) { return HexStrByteSet(ByteSet::pop_back(nb_element)); }

    private:
        string removeBaseHeader(const string &val);
        string alignToByte(const string &val, uint64_t aligned_size) const;
        uint8_t charToNibble(const char &c) const;
        char nibbleToChar(const uint8_t &nibble) const;
};