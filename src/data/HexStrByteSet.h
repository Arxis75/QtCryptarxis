#pragma once

#include <data/StrByteSet.h>

class HexStrByteSet : public StrByteSet {
    public:
        HexStrByteSet() : StrByteSet() {}
        explicit HexStrByteSet(const string &val, uint64_t aligned_size = 0);
        explicit HexStrByteSet(const ByteSet &val) : StrByteSet(val) { }
};

class BinStrByteSet : public StrByteSet {
    public:
        BinStrByteSet() : StrByteSet() {}
        explicit BinStrByteSet(const string &val, uint64_t aligned_size = 0);
        explicit BinStrByteSet(const ByteSet &val) : StrByteSet(val) { }
};

class DecStrByteSet : public StrByteSet {
    public:
        DecStrByteSet() : StrByteSet() {}
        explicit DecStrByteSet(const string &val, uint64_t aligned_size = 0);
        explicit DecStrByteSet(const ByteSet &val) : StrByteSet(val) { }

        operator string() const override;

    private:
        void construct(const string &val, uint64_t aligned_size) override;
};

class GWeiStrByteSet : public StrByteSet {
    public:
        GWeiStrByteSet() : StrByteSet() {}
        explicit GWeiStrByteSet(const string &val, uint64_t aligned_size = 0);
        explicit GWeiStrByteSet(const ByteSet &val) : StrByteSet(val) { }

        operator string() const override;

    private:
        void construct(const string &val, uint64_t aligned_size) override;
};