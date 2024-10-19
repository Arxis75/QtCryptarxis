#include <data/BinStrByteSet.h>

#include <data/Tools.h>

BinStrByteSet::BinStrByteSet(const string &val, uint64_t aligned_size)
    : IntByteSet(Integer::zero, aligned_size)
{
    regex rgx_bin("^(0b)?[0-1]+");

    if( regex_match(val, rgx_bin) )
    {
        //Constructing the ByteSet representations
        string str = alignToByte(removeBaseHeader(val), aligned_size);

        //Constructing the parent ByteSet itself
        uint8_t i_byte;
        while(str.size()) {
            // Treating each 8 bits
            i_byte =  (charToNibble(str[0]) << 7);
            i_byte += (charToNibble(str[1]) << 6);
            i_byte += (charToNibble(str[2]) << 5);
            i_byte += (charToNibble(str[3]) << 4);
            i_byte += (charToNibble(str[4]) << 3);
            i_byte += (charToNibble(str[5]) << 2);
            i_byte += (charToNibble(str[6]) << 1);
            i_byte +=  charToNibble(str[7]);
            vvalue.push_back(i_byte);
            str = str.substr(8, str.size() - 8);
        }
    }
}

BinStrByteSet::operator string() const
{
    string str;
    for(uint64_t i=0;i<byteSize();i++) {
        str += nibbleToChar((vvalue[i] & 0b10000000) >> 7);
        str += nibbleToChar((vvalue[i] & 0b01000000) >> 6);
        str += nibbleToChar((vvalue[i] & 0b00100000) >> 5);
        str += nibbleToChar((vvalue[i] & 0b00010000) >> 4);
        str += nibbleToChar((vvalue[i] & 0b00001000) >> 3);
        str += nibbleToChar((vvalue[i] & 0b00000100) >> 2);
        str += nibbleToChar((vvalue[i] & 0b00000010) >> 1);
        str += nibbleToChar( vvalue[i] & 0b00000001);
    }
    return str;
}

//TODO: move to parent abstract class
string BinStrByteSet::removeBaseHeader(const string &val) {
    string str_out = val;
    //Removes the 0x or 0b header if necessary
    if(val.size() >= 2 && val.substr(0, 2) ==  "0b")
        str_out = val.substr(2, val.size() - 2);
    return str_out;
}

string BinStrByteSet::alignToByte(const string &val, uint64_t aligned_size) const
{
    string str_out = val;
    int8_t chars_per_byte = 8;
    uint8_t unaligned_size = str_out.size()%chars_per_byte;
    string str_unaligned = str_out.substr(0, unaligned_size);
    if( unaligned_size ) {
        if( str_out.size() > unaligned_size &&   // don't remove the 0s if there is nothing else!
            str_unaligned == string(unaligned_size, '0') )
            //removes extra 0s
            str_out = str_out.substr(unaligned_size, str_out.size() - unaligned_size);
        else
            while(str_out.size()%chars_per_byte)
                //adds extra 0s
                str_out = "0" + str_out;
    }
    while(str_out.size() < aligned_size * chars_per_byte)
        //adds padding 0s if necessary
        str_out = string(chars_per_byte, '0') + str_out;
    return str_out;
}

uint8_t BinStrByteSet::charToNibble(const char &c) const
{
    uint8_t retval = 0;
    if (c >= '0' && c <= '9')
        retval = c - 48;
    else if (c >= 'A' && c <= 'F')
        retval = c - 55;
    else if (c >= 'a' && c <= 'f')
        retval = c - 87;
    return retval;
}

char BinStrByteSet::nibbleToChar(const uint8_t &nibble) const
{
    char c;
    if (nibble >= 0 && nibble <= 9)
        c = 48 + nibble;
    else if (nibble >= 0xA && nibble <= 0xF)
        c = 87 + nibble;
    return c;
}