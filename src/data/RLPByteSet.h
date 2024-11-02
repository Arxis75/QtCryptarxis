#pragma once

#include <data/ByteSet.h>

class RLPByteSet: public StrByteSet<Hex, uint8_t>
{
    public:
        // Non-encoding constructors:
        RLPByteSet() : StrByteSet() { }
        RLPByteSet(const RawByteSet &val) : StrByteSet(val) { }
        //RLPByteSet(const uint8_t *p, uint64_t size) : StrByteSet(RawByteSet(p, size)) { }
        explicit RLPByteSet(const char *str) : StrByteSet(str) { } //for raw RLP init from hex string only
        
        // Encoding constructor:
        // "as_list" is used to:
        //      - discriminates between 0x80 and 0xC0 for an empty input,
        //      - build a list over a single RLP element: this single element 
        //        must have been previously RLP-encoded and is passed as ByteSet,
        //      - rebuild an erased list header (internal use only, by pop_front()),
        RLPByteSet(const ByteSet &to_rlp_encode, const bool as_list = false);

        // Inserts a RLP into an existing RLP
        // NOTA:
        //      - If the rlp param provided is a ByteSet, a call to the RLPByteSet
        //        constructor is made prior to executing the push.
        //      - "at_top_level" used to choose between putting under existing list (false) or
        //        putting at the top level like the existing list (true), thus creating a new top-list header
        void push_back(const RLPByteSet &rlp, const bool at_top_level = false);
        void push_front(const RLPByteSet &rlp, const bool at_top_level = false);

        // Pops the front Element from a serialized RLP
        // NOTA:
        //      - if the poped RLPByteSet is a list, further calls to pop_front on this list
        //        are necessary to reach down the payload,
        //      - if the poped RLPByteSet is a string (non-list), the header is removed
        //        and thus safe to treat as a strict ByteSet payload.
        //      - if is_list = false, it is safe to cast the poped RLPByteSet to a ByteSet
        //        representing the element payload.
        RLPByteSet pop_front(bool &is_list);
};