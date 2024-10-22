#include <UI/dialog.h>

#include <QApplication>

#include <data/StrByteSet.h>

int main(int argc, char *argv[])
{
    BitStrByteSet j("11111111111111111111111111111111"
                    "11111111111111111111111111111111"
                    "11111111111111111111111111111111"
                    "11111111111111111111111111111111"
                    "11111111111111111111111111111111"
                    "11111111111111111111111111111111");
    j.push_front("11111111111111111111111111111111");
    j.push_back("11111111111111111111111111111111");
    string str_j = j;
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
    cout << string(z) << endl;
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
