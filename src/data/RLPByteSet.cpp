#include <data/RLPByteSet.h>
#include <data/Tools.h>

RLPByteSet::RLPByteSet(const ByteSet &to_rlp_encode, const bool as_list)
    : StrByteSet()
{
    //MAIN RLP ENCODING METHOD
    if( to_rlp_encode.byteSize() )
    {
        // The only use-case of as_list = true here is to rebuild the list header
        // from a truncated RLP list.The truncated RLPByteSet is passed
        // as a simple ByteSet
        uint8_t extra_prefix = (as_list ? 0x40 : 0);
        if(to_rlp_encode.byteSize() == 1 && to_rlp_encode[0] < 0x80)
        {
            if( as_list)
                ByteSet::push_back(0xC1, 1);
        }
        else if( to_rlp_encode.byteSize() <= 55 )
            ByteSet::push_back(0x80 + extra_prefix + to_rlp_encode.byteSize(), 1);
        else
        {
            uint64_t size_size = sizeInBytes64(to_rlp_encode.byteSize());
            ByteSet::push_back(0xB7 + extra_prefix + size_size, 1);
            ByteSet::push_back(to_rlp_encode.byteSize() , size_size);
        }
        RawByteSet::push_back(to_rlp_encode);
    }
    else
        ByteSet::push_back((as_list ? 0xC0 : 0x80), 1);
}

void RLPByteSet::push_back(const RLPByteSet &rlp, const bool at_top_level)
{
    //MAIN RLP LIST ENCODING METHOD
    if( byteSize() )    
    {
        //There is already some RLP data
        uint64_t list_size = byteSize();
        uint8_t list_size_size = 0;
        
        uint8_t front_header = at(0);

        if( !at_top_level && front_header >= 0xC0 )
        {
            //Drops the previous list header
            ByteSet::pop_front(1);
            if( front_header > 0xF7 )
            {
                list_size_size = front_header - 0xF7;
                ByteSet::pop_front(list_size_size);
            }
        }
        // Creates a new list header
        list_size = byteSize() + rlp.byteSize();
        if(list_size > 55)
        {
            list_size_size = sizeInBytes64(list_size);
            ByteSet::push_front(list_size, list_size_size);
        }
        ByteSet::push_front((list_size <= 55 ? 0xC0 + list_size : 0xF7 + list_size_size), 1);
    }
    RawByteSet::push_back(rlp);
}

void RLPByteSet::push_front(const RLPByteSet &rlp, const bool at_top_level)
{
    //MAIN RLP LIST ENCODING METHOD
    if( byteSize() )    
    {
        //There is already some RLP data
        uint64_t list_size = byteSize();
        uint8_t list_size_size = 0;
        
        uint8_t front_header = at(0);

        if( !at_top_level && front_header >= 0xC0 )
        {
            //Drops the previous list header
            ByteSet::pop_front(1);
            if( front_header > 0xF7 )
            {
                list_size_size = front_header - 0xF7;
                ByteSet::pop_front(list_size_size);
            }
        }

        RawByteSet::push_front(rlp);

        // Creates a new list header
        list_size = byteSize();
        if(list_size > 55)
        {
            list_size_size = sizeInBytes64(list_size);
            ByteSet::push_front(list_size, list_size_size);
        }
        ByteSet::push_front((list_size <= 55 ? 0xC0 + list_size : 0xF7 + list_size_size), 1);
    }
    else
        RawByteSet::push_front(rlp);
}

RLPByteSet RLPByteSet::pop_front(bool &is_list)
{
    is_list = false;
    RLPByteSet retval;
    if( byteSize() )
    {   
        uint8_t front_header = at(0), front_elem_size_size = 0;
        uint64_t front_header_size = 0, front_elem_size = 0;
        bool rebuild_header = false;
        
        if( front_header >= 0xC0 )
        {
            //Drops the previous list header
            RawByteSet::pop_front(1);
            if( front_header >= 0xF7 )
            {
                uint8_t list_size_size = front_header - 0xF7;
                RawByteSet::pop_front(list_size_size);
            }
            rebuild_header = true;
        }
        if( byteSize() )
        {
            front_header = at(0);

            if( front_header < 0x80 )       //[0x00, 0x7f] 
            {
                front_elem_size = 1;
                front_header_size = 0;
                is_list = false;
            }
            else if( front_header < 0xB8 )  //[0x80, 0xb7]
            {
                front_elem_size = front_header - 0x80;
                front_header_size = 1;
                is_list = false;
            }
            else if( front_header < 0xC0 )   //[0xb8, 0xbf]
            {
                front_elem_size_size = front_header - 0xB7;
                if( front_elem_size_size < byteSize() )
                    front_elem_size = (uint64_t)get(1, front_elem_size_size); //ByteSet(&at(1), front_elem_size_size).as_uint64();
                else
                {
                    cerr << "Warning! ByteSet::pop_front() found a wrong RLP encoding! Doing our best..." << endl;
                    front_elem_size = 0;
                }
                front_header_size = 1 + front_elem_size_size;
                is_list = false;
            }
            else if( front_header < 0xF8 )  //[0xc0, 0xf7]
            {
                //Do not remove the header of the sub-list when poping it:
                front_elem_size = 1 + front_header - 0xC0;
                front_header_size = 0;
                is_list = true;
            }
            else //[0xf8, 0xff] 
            {
                front_elem_size_size = front_header - 0xF7;//Do not remove the header of the sub-list when poping it
                if( front_elem_size_size < byteSize() )
                    //Do not remove the header of the sub-list when poping it:
                    front_elem_size = 1 + front_elem_size_size + (uint64_t)get(1, front_elem_size_size);
                else
                {
                    cerr << "Warning! ByteSet::pop_front() found a wrong RLP encoding! Doing our best..." << endl;
                    front_elem_size = 1;
                }
                front_header_size = 0;
                is_list = true;
            }

            //Drops the first RLP element header (only if not list)
            RawByteSet::pop_front(front_header_size);
            // Pops the first element (with header if list): the low-level vector copy
            // prevents the ByteSet to get re-RLP-encoded
            retval.RawByteSet::push_back(ByteSet::pop_front(front_elem_size));

            if( byteSize() && rebuild_header )
            {
                //Rebuilds the list header if necessary
                RLPByteSet b((*this), true);
                *this = RawByteSet(b);  //vvalue = b.vvalue;
            }
        }
    }
    return retval;
}