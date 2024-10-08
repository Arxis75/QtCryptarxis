#include <data/BitSet.h>

#include <data/Tools.h>     //To improve
#include <crypto/System.h>  //To improve: BiSet should provide operator as input for external Hashing functions

BitSet::BitSet()
    : end_boffset(0)
{}

BitSet::BitSet(const BitSet& b)
    : end_boffset(0)
{
    end_boffset = b.bitsize();
    vvalue = b.vvalue;   
}

BitSet::BitSet(const Integer& val, uint64_t bitsize)
    : end_boffset(0)
{
    set(val, bitsize);
}

BitSet::BitSet(const char *p)
    : end_boffset(0)
{
    push_back_ptr(reinterpret_cast<const u_int8_t*>(p), strlen(p)<<3);
}

BitSet::BitSet(const uint8_t *p, uint64_t bitsize)
    : end_boffset(0)
{
    push_back_ptr(p, bitsize);
}

BitSet::BitSet(const string& str_value, const uint64_t bitsize, const uint8_t in_base)
    : end_boffset(0)
{
    push_back(str_value, bitsize, in_base);
}

void BitSet::set(const Integer& val, uint64_t bitsize)
{
    if(end_boffset)
        clear();
    push_back(val, bitsize);
}

void BitSet::push_back_ptr(const uint8_t *p, uint64_t bitsize)
{
    div_t d = div(bitsize, 8);
    for(uint64_t i=0;i<d.quot;i++) vvalue.push_back(0);
    if(d.quot)
        memcpy(vvalue.data(), p, d.quot);
    if(d.rem)
        vvalue.push_back(p[d.quot] & ~(0xFF >> d.rem));
    end_boffset = bitsize;
}

void BitSet::push_back(const string& str_value, const uint64_t bitsize, const uint8_t in_base)
{
    assert( in_base == 2 || in_base ==16 );

    //Removes the 0x or 0b header if necessary
    string tmp = str_value;
    if( in_base == 16 && tmp.substr(0, 2) == "0x" )
        tmp = tmp.substr(2, tmp.size() - 2);
    else if( in_base == 2 && tmp.substr(0, 2) == "0b" )
        tmp = tmp.substr(2, tmp.size() - 2);

    Integer value(0);
    while(tmp.size()>0)
    {
        auto it = map_hexa_chars.find(tmp.substr(0, 1).c_str());
        assert( it != map_hexa_chars.end() && (in_base == 16 || (*it).second == 0 || (*it).second == 1) );
        value <<= (in_base == 16 ? 4 : 1);
        value += (*it).second;
        tmp = tmp.substr(1, tmp.size() - 1);
    }
    push_back(value, bitsize);
}

void BitSet::push_back(const Integer& bits_value, const uint64_t bitsize)
{
    Integer max_size_mask = Givaro::pow(2, bitsize) - 1;
    Integer bits_to_push(0);
    uint64_t nbitsleft = bitsize;
    while(nbitsleft)
    {   
        uint8_t nbits_to_push = min(8-(end_boffset%8), nbitsleft);
        bits_to_push = bits_value & (max_size_mask >> (bitsize - nbitsleft));
        bits_to_push >>= nbitsleft - nbits_to_push;
        if((end_boffset>>3) >= vvalue.size()) vvalue.push_back(0);  //overflow => resize
        vvalue[end_boffset>>3] += uint8_t(bits_to_push << (8-(end_boffset%8)-nbits_to_push));                
        end_boffset += nbits_to_push;
        nbitsleft -= nbits_to_push;
    }
}

const BitSet BitSet::at(uint64_t bitoffset, uint64_t bitsize) const       // not aligned
{
    assert(bitoffset+bitsize <= end_boffset);
    Integer mask = pow(2, bitsize) - 1;
    uint64_t rshift = end_boffset - bitoffset - bitsize;
    Integer v = mask & (Integer(*this)>>rshift);
    return BitSet(v, bitsize);
}

void BitSet::clear()
{
    end_boffset = 0;
    vvalue.clear();
}

const BitSet BitSet::sha256() const
{
    assert(!(end_boffset%8));
    BitSet digest(Integer::zero, 256);
    SHA256(*this, end_boffset>>3, digest);
    return digest;
}

const BitSet BitSet::keccak256() const
{
    assert(!(end_boffset%8));
    ethash::hash256 h = ethash::keccak256(*this, end_boffset>>3);
    BitSet digest(h.bytes, 256);
    return digest;
}

const BitSet BitSet::address() const
{
    assert(!(end_boffset%8));
    ethash::hash256 h = ethash::keccak256(*this, end_boffset>>3);
    BitSet digest(&h.bytes[32-20], 160);
    return digest;
}

const Integer BitSet::a2Integer(const uint8_t *input, const int32_t bitsize) const
{
    Integer output = 0;
    if(bitsize>0)
    {
        div_t d = div(bitsize,8);
        for(int32_t index=0;index<d.quot;index++)
        {
            output += input[index];
            output <<= min(bitsize - ((index+1)<<3), 8);
        }
        if(d.rem)
            output += input[d.quot] >> (8 - d.rem);
    }
    return output;
}

ostream& operator<< (ostream& out, const BitSet& v) {
    out << hex << Integer(v);
    return out;
}