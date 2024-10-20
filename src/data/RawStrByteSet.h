#pragma once

#include <data/ByteSet.h>

class RawStrByteSet : public ByteSet
{
    public:
        RawStrByteSet() : ByteSet() {}
        /// @brief Constructor from raw Char ASCII values
        /// @param val set of chars
        explicit RawStrByteSet(const string &val);
        /// @brief Constructor from the underlying ByteSet
        /// @param val undelying ByteSet
        explicit RawStrByteSet(const ByteSet &val) : ByteSet(val) {}

        //operator string() const;

        inline void push_front(const string &val) { ByteSet::push_front(RawStrByteSet(val)); }
        inline RawStrByteSet pop_front(uint64_t nb_element) { return RawStrByteSet(ByteSet::pop_front(nb_element)); }

        inline void push_back(const string &val) { ByteSet::push_back(RawStrByteSet(val)); }
        inline RawStrByteSet pop_back(uint64_t nb_element) { return RawStrByteSet(ByteSet::pop_back(nb_element)); }

    protected:
        RawStrByteSet(uint64_t resize_bytes) : ByteSet(resize_bytes) {}
};
