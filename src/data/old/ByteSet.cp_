#include <data/ByteSet.h>
#include <crypto/System.h> 

ByteSet ByteSet::pop_front(uint64_t nb_element) {
    ByteSet ret_value;
    //assert(byteSize()>=nb_element);
    if(nb_element <= byteSize())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_back(pop_front());
    return ret_value;
}

ByteSet ByteSet::pop_back(uint64_t nb_element) {
    ByteSet ret_value;
    //assert(byteSize()>=nb_element);
    if(nb_element <= byteSize())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_front(pop_back());
    return ret_value;
}

uint8_t ByteSet::pop_front()
{
    assert(byteSize());
    uint8_t ret_value = vvalue[0];
    vvalue.erase(vvalue.begin());
    return ret_value;
}

uint8_t ByteSet::pop_back()
{
    assert(byteSize());
    uint8_t ret_val = vvalue[byteSize()-1];
    vvalue.pop_back();
    return ret_val;
}

ByteSet::operator string() const {
    stringstream ss;
    ss << "0x";
    for(uint64_t i=0;i<byteSize();i++) {
        ss << std::setfill('0') << std::setw(2) << hex << int(vvalue[i]);
    }
    return ss.str();     
}

ostream& operator<< (ostream& out, const ByteSet &v) {
    out << (string)v;
    return out;
}

ByteSet ByteSet::sha256() const
{
    ByteSet digest(32);
    if(byteSize())
        SHA256(&vvalue[0], byteSize(), &digest.vvalue[0]);
    return digest;
}

ByteSet ByteSet::keccak256() const
{
    ByteSet digest;
    if(byteSize()) {
        hash256 h = ethash::keccak256(&vvalue[0], byteSize());
        for(uint64_t i=0;i<32;i++)
            digest.push_back(h.bytes[i]);
    }
    return digest;
}

ByteSet ByteSet::generateRandom(uint32_t byte_size)
{
    int retval = -1;
    ByteSet random_buffer(byte_size), random_set(byte_size);
    retval = RAND_bytes(&random_buffer.vvalue[0], byte_size);

    if( retval > 0 )
        for(uint64_t i=0;i<byte_size;i++)
            random_set.push_back(random_buffer.vvalue[i]);
    return random_set;
}

/******************************************************************************************** */

BitSet BitSet::pop_front(uint64_t nb_element)
{   
    BitSet ret;
    assert(bitSize()>=nb_element);
    for(uint64_t i=0;i<nb_element;i++)
        ret.push_back(pop_front());
    return ret; 
}

BitSet BitSet::pop_back(uint64_t nb_element)
{
    BitSet ret;
    assert(bitSize()>=nb_element);
    for(uint64_t i=0;i<nb_element;i++)
        ret.push_front(pop_back());
    return ret; 
}

BitSet::operator string() const {
    stringstream ss;
    ss << "0b";
    for(uint64_t i=0;i<bitSize();i++)
        ss << dec << bool(vvalue[i]);
    return ss.str();     
}

BitSet BitSet::at(uint64_t bitoffset, uint64_t bitsize) const       // not aligned
{
    assert(bitoffset+bitsize <= bitSize());
    BitSet tmp(*this);
    tmp.pop_front(bitoffset);
    tmp.pop_back(tmp.bitSize()-bitsize);
    return tmp;
}


ByteSet BitSet::toByteSet() const
{
    BitSet from = *this;
    ByteSet to;
    uint8_t i_byte = 0;
    if(from.bitSize()%8) {
        //Force Byte-alignment of non-aligned bitset
        while(from.bitSize()%8)
            i_byte += (from.pop_front() << (from.bitSize()%8));
        to.push_back(i_byte);
    }
    while(from.bitSize()) {
        i_byte = 0;
        for(uint64_t j=0;j<8;j++)
            i_byte += (from.pop_front() << (from.bitSize()%8));
        to.push_back(i_byte);
    }
    return to;
}