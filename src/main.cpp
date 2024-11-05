#include <UI/dialog.h>

#include <QApplication>

#include <data/ByteSet.h>
#include <data/Tools.h>

/*template<typename T = uint8_t>
class toto : public RawByteSet<toto, T>
{
public:
    toto() {}
};*/

int main(int argc, char *argv[])
{
    /*int x;

    cin >> x;
    
    cout << char(60) << endl;*/

    /*RawByteSet<toto, bool> vv0, vvv0;

    vv0.push_back_elem(true);
    vv0.push_back_elem(false);
    vv0.push_back_elem(true);
    vv0.push_back_elem(false);
    vv0.push_back_elem(true);
    vv0.push_back_elem(false);
    vv0.push_back_elem(true);
    vv0.push_back_elem(false);
    vv0.push_back_elem(true);    
    vv0.push_back_elem(false);
    vv0.push_back_elem(true);

    RawByteSet<toto, uint8_t> vv1(vv0);

    vvv0 = vv1;

    RawByteSet<ByteSet> vv;
    ByteSet bs;
    StrByteSet bsv;
    StrByteSet<Bin, bool> bbsv;

    vv = RawByteSet<ByteSet>();
    vv.resize(32);
    bs = ByteSet(RawByteSet<ByteSet>());
    bs.resize(32);

    StrByteSet<Hex, bool>  bsv1("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    cout << hex << (Integer) bsv1 << endl;
    StrByteSet<Hex, uint8_t>   bsv8("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    cout << hex << (Integer)bsv8 << endl;

    cout << ByteSet<bool>::generateRandom(256) << endl;
    cout << ByteSet<uint8_t>::generateRandom(32) << endl;

    cout << bsv1.keccak256() << endl;
    cout << bsv1.sha256() << endl;
    cout << bsv8 << endl;

    cout << bsv1.toFormat(Dec) << endl;
    cout << bsv8.toFormat(Dec) << endl;

    cout << bsv1.toFormat(GWei) << endl;
    cout << bsv8.toFormat(GWei) << endl;
    
    cout << bsv1.toFormat(Bin) << endl;
    cout << bsv8.toFormat(Bin) << endl;

    StrByteSet<Dec, bool>      bsv1d  = StrByteSet<Dec, bool>("115792089237316195423570985008687907853269984665640564039457584007908834671663");
    cout << hex << (Integer)bsv1d << endl;
    StrByteSet<Dec, uint8_t>   bsv8d  = StrByteSet<Dec, uint8_t>("115792089237316195423570985008687907853269984665640564039457584007908834671663");
    cout << hex << (Integer)bsv8d << endl;
 
    cout << bsv1d << endl;
    cout << bsv8d << endl;

    StrByteSet<Bin, bool>      bsv1b  = StrByteSet<Bin, bool>("11111111111");
    cout << hex << (Integer)bsv1b << endl;
    StrByteSet<Bin, uint8_t>   bsv8b  = StrByteSet<Bin, uint8_t>("11111111111");
    cout << hex << (Integer)bsv8b << endl;
 
    cout << bsv1b << endl;
    cout << bsv8b << endl;

    bsv = StrByteSet("0x0F", 17);
    bsv = StrByteSet<Dec>("127", 17);
    bsv = StrByteSet<Bin>("0b1111111", 17);
    bbsv = StrByteSet<Bin, bool>("0b1111111",17);*/

    /*int x = 0b00010000;

    Integer large_int("115792089237316195423570985008687907853269984665640564039457584007908834671663");
    uint8_t zz[3] = {0x00, 0x01, 0x02};
    
    vv = RawByteSet<ByteSet<>>(zz, sizeof(zz));     //implicit not possible
    vv = RawByteSet(0);                             //implicit possible
    vv = RawByteSet(0, 32);                         //implicit not possible
    vv = RawByteSet(0x123456789ABCDEF);             //implicit possible
    vv = RawByteSet(0x123456789ABCDEF, 17);         //implicit not possible
    vv = RawByteSet(Integer::zero);             //implicit possible
    vv = RawByteSet(Integer::zero, 17);         //implicit not possible
    vv = RawByteSet(large_int);             //implicit possible
    vv = RawByteSet(large_int, 17);         //implicit not possible
    vv = RawByteSet("");
    vv = RawByteSet("", 17);
    vv = RawByteSet("0x123456789ABCDEF");
    vv = RawByteSet("0x123456789ABCDEF", 17);

    vv = RawByteSet(ByteSet(0));                             //implicit possible
    vv = RawByteSet(ByteSet(0, 32));                         //implicit not possible
    vv = RawByteSet(ByteSet(0x123456789ABCDEF));             //implicit possible
    vv = RawByteSet(ByteSet(0x123456789ABCDEF, 17));         //implicit not possible
    vv = RawByteSet(ByteSet(Integer::zero));             //implicit possible
    vv = RawByteSet(ByteSet(Integer::zero, 17));         //implicit not possible
    vv = RawByteSet(ByteSet(large_int));             //implicit possible
    vv = RawByteSet(ByteSet(large_int, 17));         //implicit not possible
    vv = RawByteSet(StrByteSet(""));
    vv = RawByteSet(StrByteSet("", 17));
    vv = RawByteSet(StrByteSet("0x123456789ABCDEF"));
    vv = RawByteSet(StrByteSet("0x123456789ABCDEF", 17));

    //bs = ByteSet(zz, sizeof(zz));                  //implicit not possible
    //bs = ByteSet((zz, sizeof(zz)));                  //implicit not possible
    bs = ByteSet(0);                             //implicit possible
    bs = ByteSet(0, 32);                         //implicit not possible
    bs = ByteSet(0x123456789ABCDEF);             //implicit possible
    bs = ByteSet(0x123456789ABCDEF, 17);         //implicit not possible
    bs = ByteSet(Integer::zero);             //implicit possible
    bs = ByteSet(Integer::zero, 17);         //implicit not possible
    bs = ByteSet(large_int);             //implicit possible
    bs = ByteSet(large_int, 17);         //implicit not possible
    //bs = ByteSet("");
    //bs = ByteSet("", 17);
    //bs = ByteSet("0x123456789ABCDEF");
    //bs = ByteSet("0x123456789ABCDEF", 17);*/

    /*bs = ByteSet(RawByteSet<ByteSet<>>(zz, sizeof(zz)));                    //implicit not possible
    bs = ByteSet(StrByteSet(""));
    bs = ByteSet(StrByteSet("", 17));
    bs = ByteSet(StrByteSet("0x123456789ABCDEF"));
    bs = ByteSet(StrByteSet("0x123456789ABCDEF", 17));
    
    //bsv = StrByteSet(zz, sizeof(zz));
    bsv = StrByteSet(0);                          //implicit possible
    bsv = StrByteSet(0, 32);                      //implicit not possible
    bsv = StrByteSet(0x123456789ABCDEF);          //implicit possible
    bsv = StrByteSet(0x123456789ABCDEF, 17);      //implicit not possible
    bsv = StrByteSet(Integer::zero);          //implicit possible
    bsv = StrByteSet(Integer::zero, 17);      //implicit not possible
    bsv = StrByteSet(large_int);          //implicit possible
    bsv = StrByteSet(large_int, 17);      //implicit not possible
    bsv = StrByteSet("");
    bsv = StrByteSet("", 17);
    bsv = StrByteSet("0x123456789ABCDEF");
    bsv = StrByteSet("0x123456789ABCDEF", 17);

    bsv = StrByteSet(RawByteSet<StrByteSet<>>(zz, sizeof(zz)));
    bsv = StrByteSet(ByteSet(Integer::zero));          //implicit possible
    bsv = StrByteSet(ByteSet(Integer::zero, 17));      //implicit not possible
    bsv = StrByteSet(ByteSet(large_int));          //implicit possible
    bsv = StrByteSet(ByteSet(large_int, 17));      //implicit not possible

    vv = bs;
    vv = bsv;
    bs = vv;
    bs = bsv;
    bsv = vv;
    bsv = bs;*/

    /*BinStrBitSet i("0b111111111");
    i.push_back("0b1");
    i.push_front("0b1");
    cout << (string)i << endl;

    BitByteSet j((BinStrBitSet)"0b11111111111");
    cout << (string)j << endl;

    BinStrByteSet k((BinStrByteSet)"0b11111111111");
    cout << (string)k << endl;

    BinStrBitSet l((string)k);
    cout << (string)l << endl;

    cout << i.keccak256() << endl;
    cout << j.keccak256() << endl;
    cout << k.keccak256() << endl;
    cout << l.keccak256() << endl;*/

    /*string str_j = j;
    cout << str_j << endl;
    
    BinStrByteSet bj = j.toBinStrByteSet();
    string str_bj = bj;
    cout << str_bj << endl;

    GWeiStrByteSet i("8.050351573");
    
    string str_i = i;
    cout << str_i << endl;

    HexStrByteSet f("0x0");

    HexStrByteSet x("0x00123456789ABCDEF", 17);
    cout << string(x) << endl;
    //ByteSet x("0x10000000000000009", 17, 16);
    DecStrByteSet y(x);
    cout << string(y) << endl;
    IntByteSet z(y);
    cout << string(z) << endl;*/
    /*string yy = y.toHex();
    yy = y.toDec();
    yy = y.toBin();

    yy = y.toFixedHex(32);
    yy = y.toFixedBin(32);*/

/*    //dec string => hex string
    stringstream ss;
    ss << std::hex << Integer("65535");
    string out = ss.str();

    out = addZeroPadding("0x0000F", 16, 3);

    //hex string => dec string
    out = toHex("zzzzz", 10);
    out = toHex("0x12AB", 10);
    out = toHex("12AB", 10); 
    out = toHex("0x12ab", 10);
    out = toHex("12ab", 10);
    out = toDec("zzzzz", 2);
    out = toHex("0x12AB", 2);
    out = toHex("12AB", 2);
    out = toHex("0x12ab", 2);
    out = toHex("12ab", 2);
    out = toHex("65536", 2);

    out = toDec("zzzzz", 16);
    out = toDec("zzzzz", 2);
    out = toDec("0x12AB", 2);
    out = toDec("12AB", 2);
    out = toDec("0x12ab", 2);
    out = toDec("12ab", 2);
    out = toDec("65536", 2);

    out = toBin("zzzzz", 16);
    out = toBin("zzzzz", 10);
    out = toBin("0x12AB", 10);
    out = toBin("12AB", 10);
    out = toBin("0x12ab", 10);
    out = toBin("12ab", 10);

    //hex string => dec string
    out = toDec(removeBaseHeader("0b111"), 2);
    out = toDec(removeBaseHeader("0b11111"), 2);
    out = toDec(removeBaseHeader("0x12AB"), 16);
    out = toDec("12AB", 16);
    out = toDec(removeBaseHeader("0x12ab"), 16);
    out = toDec("12ab", 16);*/

    QApplication a(argc, argv);
    Dialog d;
    d.show();
    return a.exec();
}