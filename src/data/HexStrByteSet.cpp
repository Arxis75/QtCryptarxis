#include "HexStrByteSet.h"

#include <data/Tools.h>

HexStrByteSet::HexStrByteSet(const string &val, uint64_t aligned_size)
    : StrByteSet(val, "0x", "^(0x)?[0-9a-fA-F]+", true, 2, aligned_size)
{ }

BinStrByteSet::BinStrByteSet(const string &val, uint64_t aligned_size)
    : StrByteSet(val, "0b", "^(0b)?[0-1]+", true, 8, aligned_size)
{ }

DecStrByteSet::DecStrByteSet(const string &val, uint64_t aligned_size)
    : StrByteSet(val, "", "^[0-9]+", false, 0, aligned_size)
{ }

void DecStrByteSet::construct(const string &val, uint64_t aligned_size)
{
    //Constructing the ByteSet representations
    Integer val_dec(val.c_str());
    *this = (DecStrByteSet)IntByteSet(val_dec, aligned_size);
}

DecStrByteSet::operator string() const
{
    stringstream ss;
    ss << dec << *this;
    return ss.str(); 
}

GWeiStrByteSet::GWeiStrByteSet(const string &val, uint64_t aligned_size)
    : StrByteSet(val, "", "^[0-9]+.[0-9]{9}", false, 0, aligned_size)
{ }

void GWeiStrByteSet::construct(const string &val, uint64_t aligned_size)
{
    //Constructing the ByteSet representations
    Integer val_dec(removeCharsFromString(val.c_str(), ".").c_str());
    *this = (GWeiStrByteSet)IntByteSet(val_dec, aligned_size);
}

GWeiStrByteSet::operator string() const
{
    string str_wei(DecStrByteSet(*this));
    while(str_wei.size() < 10)
        str_wei = "0" + str_wei;
    return str_wei.substr(0, str_wei.size() - 9) + "." + str_wei.substr(str_wei.size() - 9, 9);
}