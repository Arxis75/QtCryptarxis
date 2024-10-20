#include "DecStrByteSet.h"
#include "HexStrByteSet.h"

#include <data/Tools.h>

DecStrByteSet::DecStrByteSet(const string &val, uint64_t aligned_size)
    : IntByteSet()
{
    regex rgx_dec("^[0-9]+");

    if( regex_match(val, rgx_dec) )
    {
        //Constructing the ByteSet representations
        Integer val_dec(val.c_str());
        vvalue = (vector<uint8_t>)IntByteSet(val_dec, aligned_size);
    }
}

DecStrByteSet::operator string() const
{
    stringstream ss;
    ss << dec << *this;
    return ss.str(); 
}