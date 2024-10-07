#include <data/ByteSet.h>

#include <crypto/System.h>  //To improve: ByteSet should provide operator as input for external Hashing functions

ByteSet::ByteSet(const Integer& value, uint64_t size)
{
    vvalue.reserve(size);
    uint64_t value_size = (size > sizeInBytes(value) ? sizeInBytes(value) : size);
    uint64_t extra_size = size - value_size;
    for(int i=0;i<extra_size;i++)
        vvalue.push_back(0x00);
    for(int i=1;i<=value_size;i++)
        vvalue.push_back(0xFF & uint8_t(value>>((value_size-i)<<3)));
}

void ByteSet::push_back_ptr(const uint8_t *p, uint64_t size)
{
    for(uint64_t i=0;i<size;i++)
        vvalue.push_back(p[i]);
}

void ByteSet::push_back(const string& str_value, const uint64_t size, const uint8_t in_base)
{
    assert( in_base == 2 || in_base ==16 );
    
    //Removes the 0x or 0b header if necessary
    string tmp = str_value;
    if( in_base == 16 && tmp.substr(0,2) == "0x" )
        tmp = tmp.substr(2, tmp.size() - 2);
    else if( in_base == 2 && tmp.substr(0,2) == "0b" )
        tmp = tmp.substr(2, tmp.size() - 2);

    //Forces byte-alignment if ncesessary
    int32_t front_zero_padding_size = (in_base == 16 ? tmp.size()%2 : tmp.size()%8);
    while( front_zero_padding_size )
    {
        tmp = string("0") + tmp;
        front_zero_padding_size = (in_base == 16 ? tmp.size()%2 : tmp.size()%8);
    }

    //Stores front 00-padding according to "size" if ncesessary
    front_zero_padding_size = size - (in_base == 16 ? tmp.size()>>1 : tmp.size()>>3);
    for(int i=0;i<front_zero_padding_size;i++)
        vvalue.push_back(0x00);

    //If empty ByteSet, optimizes the memory allocation
    if( !byteSize() )
        vvalue.reserve(in_base == 16 ? tmp.size()>>1 : tmp.size()>>3);

    while(tmp.size()>0)
    {
        uint8_t value = 0;
        uint8_t nb_chars_in_one_byte = (in_base == 16 ? 2 : 8);
        for(int i=0;i<nb_chars_in_one_byte;i++)
        {
            auto it = map_hexa_chars.find(tmp.substr(0, 1).c_str());
            assert( it != map_hexa_chars.end() && (in_base == 16 || (*it).second == 0 || (*it).second == 1) );
            value <<= (in_base == 16 ? 4 : 1);
            value += (*it).second;
            tmp = tmp.substr(1, tmp.size() - 1);
        }
        vvalue.push_back(value);
    }
}

void ByteSet::push_back(const uint64_t value, const uint64_t size)
{
    //Factorize code with push_front(const uint64_t value, const uint64_t size)
    ByteSet b;
    uint64_t value_size = (size > 8 ? 8 : size);
    uint64_t extra_size = size - value_size;
    for(int i=0;i<extra_size;i++)
        b.vvalue.push_back(0x00);
    for(int i=1;i<=value_size;i++)
        b.vvalue.push_back(0xFF & uint8_t(value>>((value_size-i)<<3)));
    push_back(b);
 };

const void ByteSet::push_front(const uint64_t value, const uint64_t size)
{
    //Factorize code with push_back(const uint64_t value, const uint64_t size)
    ByteSet b;
    uint64_t value_size = (size > 8 ? 8 : size);
    uint64_t extra_size = size - value_size;
    for(int i=0;i<extra_size;i++)
        b.vvalue.push_back(0x00);
    for(int i=1;i<=value_size;i++)
        b.vvalue.push_back(0xFF & uint8_t(value>>((value_size-i)<<3)));
    push_front(b);
}

const ByteSet ByteSet::pop_front(const uint64_t size)
{
    if( size )
    {
        if( size < byteSize() )
        {
            ByteSet retval(&(*this)[0], size);
            memmove(&(*this)[0], &(*this)[size], byteSize() - size);    //overlapping memcpy
            for(int i=0;i<size;i++)
                vvalue.pop_back();
            return retval;
        }
        else
        {
            if( size > byteSize() )
                cerr << "Warning! ByteSet::pop_front() asked to pop data larger than the ByteSet size! The whole buffer was poped but not more..." << endl;
            ByteSet retval(*this);
            clear();
            return retval;
        }
    }
    else
        return ByteSet();
}

const ByteSet ByteSet::sha256() const
{
    uint8_t zero[32];
    memset(&zero,0,sizeof(zero));
    ByteSet digest(&zero[0], sizeof(zero));
    SHA256(*this, byteSize(), digest);
    return digest;
}

const ByteSet ByteSet::keccak256() const
{
    ethash::hash256 h = ethash::keccak256(*this, byteSize());
    ByteSet digest(h.bytes, 32);
    return digest;
}

const ByteSet ByteSet::generateRandom(const uint32_t size)
{
    int retval = -1;
    ByteSet random_set;
    uint8_t random_buffer[size];
    memset(&random_buffer, 0, size);
    
    retval = RAND_bytes(&random_buffer[0], size);

    if( retval > 0 )
        random_set = ByteSet(&random_buffer[0], size);
    return random_set;
}

const Integer ByteSet::a2Integer(const uint8_t *input, const int32_t size) const
{
    Integer output = 0;
    if(size>0)
    {
        for(int32_t index=0;index<size;index++)
        {
            output <<= 8;
            output += input[index];
        }
    }
    return output;
}

ByteSet::operator const string() const
{
    uint64_t size = byteSize();
    string s("");
    for (uint64_t i = 0; i < size; i++)
        s += vvalue[i];
    return s;
}

const uint64_t ByteSet::as_uint64() const
{
    uint64_t retval = 0;
    if( vvalue.size() )
    {
        uint8_t s_1 = vvalue.size() - 1;
        if(s_1 > 7)     
            s_1 = 7;    // 7 = 8 bytes (uint64_t) - 1
        for(int i=0;i<=s_1;i++)
            retval += uint64_t(vvalue[i]) << ((s_1 - i) << 3 );
    }
    return retval;
}

ostream& operator<< (ostream& out, const ByteSet &v) {
    //out << hex << Integer(v);
    out << Integer(v);
    return out;
}
