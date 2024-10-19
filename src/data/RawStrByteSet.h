#pragma once

#include <data/ByteSet.h>

class RawStrByteSet : public ByteSet
{
    public:
        /// @brief Constructor from raw Char ASCII values
        /// @param val set of chars
        explicit RawStrByteSet(const string &val);
        /// @brief Constructor from the underlying ByteSet
        /// @param val undelying ByteSet
        explicit RawStrByteSet(const ByteSet &val);

        inline operator string() const { return m_str; };
    
    private:
        string m_str;
};
