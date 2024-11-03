#include <data/RLPByteSet.h>
#include <data/Tools.h>

RLPByteSet::RLPByteSet(const ByteSet &to_rlp_encode, const bool as_list)
    : ByteSet()
{
    //MAIN RLP ENCODING METHOD
    uint64_t val_size = to_rlp_encode.byteSize();
    if( val_size )
    {
        // The only use-case of as_list = true here is to rebuild the list header
        // from a header-truncated RLP list.The header-truncated RLP list is passed
        // as a simple ByteSet
        uint8_t extra_prefix = (as_list ? 0x40 : 0);
        if(val_size == 1 && to_rlp_encode[0] < 0x80)
        {
            if( as_list )
                ByteSet::push_back(0xC1);
        }
        else if( val_size <= 55 )
            ByteSet::push_back(0x80 + extra_prefix + val_size);
        else
        {
            uint64_t val_size_size = sizeInBytes64(val_size);
            ByteSet::push_back(0xB7 + extra_prefix + val_size_size);
            ByteSet::push_back(val_size , val_size_size);
        }
        ByteSet::push_back(to_rlp_encode);
    }
    else
        ByteSet::push_back((as_list ? 0xC0 : 0x80));
}

void RLPByteSet::push_back(const RLPByteSet &rlp, const bool at_top_level)
{
    //MAIN RLP LIST ENCODING METHOD
    if( byteSize() ) {
        //Shall it be put under an existing top-list?
        if(!at_top_level)
            //Yes => drop the previous header, it will be recalculated below
            dropListHeader();
        // Creates a new list header
        ByteSet::push_back(rlp);
        addListHeader();
    }
    else
        ByteSet::push_back(rlp);
}

void RLPByteSet::push_front(const RLPByteSet &rlp, const bool at_top_level)
{
    //MAIN RLP LIST ENCODING METHOD
    if( byteSize() ) {
        //Shall it be put under an existing top-list?
        if(!at_top_level)
            //Yes => drop the previous header, it will be recalculated below
            dropListHeader();
        ByteSet::push_front(rlp);
        addListHeader();
    }
    else
        ByteSet::push_front(rlp);
}

bool RLPByteSet::dropListHeader() 
{   bool is_dropped = false;
    //Shall it be put under an existing top-list?
    uint8_t front_header = at(0);
    if( front_header >= 0xC0 ) {
        //Drops the previous list header
        ByteSet::pop_front();
        if( front_header > 0xF7 ) {
            uint8_t list_size_size = front_header - 0xF7;
            ByteSet::pop_front(list_size_size);
        }
        is_dropped = true;
    }
    return is_dropped;
}

void RLPByteSet::addListHeader() 
{   
    // Creates a new list header
    uint64_t list_size = byteSize();
    if(list_size > 55) {
        uint8_t list_size_size = sizeInBytes64(list_size);
        ByteSet::push_front(list_size, list_size_size);
        ByteSet::push_front(0xF7 + list_size_size);
    }
    else
        ByteSet::push_front(0xC0 + list_size);
}

RLPByteSet RLPByteSet::pop_front(bool &is_list)
{
    is_list = false;
    RLPByteSet retval;
    try
    {
        if( byteSize() )
        {          
            //Drops the previous list header if necessary
            // and flags it for reconstruction.
            bool rebuild_header = dropListHeader();

            if( byteSize() )
            {
                uint8_t front_header = 0, front_elem_size_size = 0;
                uint64_t front_header_size = 0, front_elem_size = 0;

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
                    front_elem_size = (uint64_t)get(1, front_elem_size_size);
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
                    front_elem_size_size = front_header - 0xF7;
                    //Do not remove the header of the sub-list when poping it:
                    front_elem_size = 1 + front_elem_size_size + (uint64_t)get(1, front_elem_size_size);
                    front_header_size = 0;
                    is_list = true;
                }

                //Drops the first RLP element header (only if not list)
                ByteSet::pop_front(front_header_size);
                // Pops the first element (with header if list): the low-level vector copy
                // prevents the ByteSet to get re-RLP-encoded
                *static_cast<ByteSet*>(&retval) = ByteSet::pop_front(front_elem_size);

                if( byteSize() && rebuild_header )
                {
                    //Rebuilds the list header if necessary
                    RLPByteSet b((*this), true);
                    *this = RawByteSet(b);
                }
            }
        }
    }
    catch(const std::exception& e) {
        cout << "invalid RLP: " << e.what() << endl;
    }
    return retval;
}