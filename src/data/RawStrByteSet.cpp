#include "RawStrByteSet.h"

#include <data/Tools.h>

RawStrByteSet::RawStrByteSet(const string &val)
    : ByteSet()
    , m_str(val)
{
    //Constructing the parent ByteSet
    string tmp_str(val);
    while(tmp_str.size()) {
        // Treat each char as a raw Byte
        vvalue.push_back(char(tmp_str[0]));
        tmp_str = tmp_str.substr(1, tmp_str.size() - 1);
    }
}

RawStrByteSet::RawStrByteSet(const ByteSet &val)
    : ByteSet(val)
{
    for(uint64_t i=0;i< byteSize();i++)
        // Treat each underlying byte as a raw Char
        m_str += char(vvalue[i]);
}