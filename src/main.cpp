#include <UI/dialog.h>

#include <QApplication>

#include <data/byteSet.h>
#include <data/Tools.h>

template<typename T = uint8_t>
class toto
{
public:
    toto() {}
};

int main(int argc, char *argv[])
{
    ValueVector<toto, bool> vv0, vvv0;

    vv0.push_back(true);
    vv0.push_back(false);
    vv0.push_back(true);
    vv0.push_back(false);
    vv0.push_back(true);
    vv0.push_back(false);
    vv0.push_back(true);
    vv0.push_back(false);
    vv0.push_back(true);    
    vv0.push_back(false);
    vv0.push_back(true);

    ValueVector<toto, uint8_t> vv1(vv0);

    vvv0 = vv1;

    ValueVector<byteSet> vv;
    byteSet bs;
    byteSetView bsv;
    byteSetView<Bin, bool> bbsv;

    vv = ValueVector<byteSet>();
    vv.resize(32);
    bs = byteSet(ValueVector<byteSet>());
    bs.resize(32);

    byteSetView<Hex, bool>  bsv1("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    cout << hex << (Integer) bsv1 << endl;
    byteSetView<Hex, uint8_t>   bsv8("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    cout << hex << (Integer)bsv8 << endl;

    cout << byteSet<bool>::generateRandom(256) << endl;
    cout << byteSet<uint8_t>::generateRandom(32) << endl;

    cout << bsv1.keccak256() << endl;
    cout << bsv1.sha256() << endl;
    cout << bsv8 << endl;

    cout << bsv1.toFormat(Dec) << endl;
    cout << bsv8.toFormat(Dec) << endl;

    cout << bsv1.toFormat(GWei) << endl;
    cout << bsv8.toFormat(GWei) << endl;
    
    cout << bsv1.toFormat(Bin) << endl;
    cout << bsv8.toFormat(Bin) << endl;

    byteSetView<Dec, bool>      bsv1d  = byteSetView<Dec, bool>("115792089237316195423570985008687907853269984665640564039457584007908834671663");
    cout << hex << (Integer)bsv1d << endl;
    byteSetView<Dec, uint8_t>   bsv8d  = byteSetView<Dec, uint8_t>("115792089237316195423570985008687907853269984665640564039457584007908834671663");
    cout << hex << (Integer)bsv8d << endl;
 
    cout << bsv1d << endl;
    cout << bsv8d << endl;

    byteSetView<Bin, bool>      bsv1b  = byteSetView<Bin, bool>("11111111111");
    cout << hex << (Integer)bsv1b << endl;
    byteSetView<Bin, uint8_t>   bsv8b  = byteSetView<Bin, uint8_t>("11111111111");
    cout << hex << (Integer)bsv8b << endl;
 
    cout << bsv1b << endl;
    cout << bsv8b << endl;

    bsv = byteSetView("0x0F", 17);
    bsv = byteSetView<Dec>("127", 17);
    bsv = byteSetView<Bin>("0b1111111", 17);
    bbsv = byteSetView<Bin, bool>("0b1111111",17);

    /*int x = 0b00010000;

    Integer large_int("115792089237316195423570985008687907853269984665640564039457584007908834671663");
    uint8_t zz[3] = {0x00, 0x01, 0x02};
    
    vv = ValueVector<byteSet<>>(zz, sizeof(zz));     //implicit not possible
    vv = ValueVector(0);                             //implicit possible
    vv = ValueVector(0, 32);                         //implicit not possible
    vv = ValueVector(0x123456789ABCDEF);             //implicit possible
    vv = ValueVector(0x123456789ABCDEF, 17);         //implicit not possible
    vv = ValueVector(Integer::zero);             //implicit possible
    vv = ValueVector(Integer::zero, 17);         //implicit not possible
    vv = ValueVector(large_int);             //implicit possible
    vv = ValueVector(large_int, 17);         //implicit not possible
    vv = ValueVector("");
    vv = ValueVector("", 17);
    vv = ValueVector("0x123456789ABCDEF");
    vv = ValueVector("0x123456789ABCDEF", 17);

    vv = ValueVector(byteSet(0));                             //implicit possible
    vv = ValueVector(byteSet(0, 32));                         //implicit not possible
    vv = ValueVector(byteSet(0x123456789ABCDEF));             //implicit possible
    vv = ValueVector(byteSet(0x123456789ABCDEF, 17));         //implicit not possible
    vv = ValueVector(byteSet(Integer::zero));             //implicit possible
    vv = ValueVector(byteSet(Integer::zero, 17));         //implicit not possible
    vv = ValueVector(byteSet(large_int));             //implicit possible
    vv = ValueVector(byteSet(large_int, 17));         //implicit not possible
    vv = ValueVector(byteSetView(""));
    vv = ValueVector(byteSetView("", 17));
    vv = ValueVector(byteSetView("0x123456789ABCDEF"));
    vv = ValueVector(byteSetView("0x123456789ABCDEF", 17));

    //bs = byteSet(zz, sizeof(zz));                  //implicit not possible
    //bs = byteSet((zz, sizeof(zz)));                  //implicit not possible
    bs = byteSet(0);                             //implicit possible
    bs = byteSet(0, 32);                         //implicit not possible
    bs = byteSet(0x123456789ABCDEF);             //implicit possible
    bs = byteSet(0x123456789ABCDEF, 17);         //implicit not possible
    bs = byteSet(Integer::zero);             //implicit possible
    bs = byteSet(Integer::zero, 17);         //implicit not possible
    bs = byteSet(large_int);             //implicit possible
    bs = byteSet(large_int, 17);         //implicit not possible
    //bs = byteSet("");
    //bs = byteSet("", 17);
    //bs = byteSet("0x123456789ABCDEF");
    //bs = byteSet("0x123456789ABCDEF", 17);*/

    /*bs = byteSet(ValueVector<byteSet<>>(zz, sizeof(zz)));                    //implicit not possible
    bs = byteSet(byteSetView(""));
    bs = byteSet(byteSetView("", 17));
    bs = byteSet(byteSetView("0x123456789ABCDEF"));
    bs = byteSet(byteSetView("0x123456789ABCDEF", 17));
    
    //bsv = byteSetView(zz, sizeof(zz));
    bsv = byteSetView(0);                          //implicit possible
    bsv = byteSetView(0, 32);                      //implicit not possible
    bsv = byteSetView(0x123456789ABCDEF);          //implicit possible
    bsv = byteSetView(0x123456789ABCDEF, 17);      //implicit not possible
    bsv = byteSetView(Integer::zero);          //implicit possible
    bsv = byteSetView(Integer::zero, 17);      //implicit not possible
    bsv = byteSetView(large_int);          //implicit possible
    bsv = byteSetView(large_int, 17);      //implicit not possible
    bsv = byteSetView("");
    bsv = byteSetView("", 17);
    bsv = byteSetView("0x123456789ABCDEF");
    bsv = byteSetView("0x123456789ABCDEF", 17);

    bsv = byteSetView(ValueVector<byteSetView<>>(zz, sizeof(zz)));
    bsv = byteSetView(byteSet(Integer::zero));          //implicit possible
    bsv = byteSetView(byteSet(Integer::zero, 17));      //implicit not possible
    bsv = byteSetView(byteSet(large_int));          //implicit possible
    bsv = byteSetView(byteSet(large_int, 17));      //implicit not possible

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