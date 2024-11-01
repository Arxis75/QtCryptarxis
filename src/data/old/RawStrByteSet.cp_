#include <data/RawStrByteSet.h>
#include <data/Tools.h>

RawStrByteSet::RawStrByteSet(const string &val)
    : ByteSet()
{
    //Constructing the parent ByteSet
    string tmp_str(val);
    while(tmp_str.size()) {
        // Treat each char as a raw Byte
        vvalue.push_back(char(tmp_str[0]));
        tmp_str = tmp_str.substr(1, tmp_str.size() - 1);
    }
}

RawStrByteSet::operator string() const
{
    string str;
    for(uint64_t i=0;i<byteSize();i++)
        // Treat each underlying byte as a raw Char
        str += char(vvalue[i]);
    return str;
}