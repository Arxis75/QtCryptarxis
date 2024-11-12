#include <UI/dialog.h>
#include <QApplication>

#include <data/Bip39SeedFormat.h>

int main(int argc, char *argv[])
{
    /*string ent = Bip39Mnemonic24.toCanonicalString("again  SCissors moon goose guess antique neither ticket window wealth avoid sleep snow casual public grass define despair dry excuse manual buffalo "
                                                   "whisper " );
    ent += "000";
    string mnc = Bip39Mnemonic24.toUserString(ent);*/
    
    /*int x;

    for(int i = 0;i<101;i++)
    {
       cout << i << endl; 
    }
    cout << "Entrez un chiffre:" << endl;
    cin >> x;
    cout << "357 * x = " << 357 * x << endl;*/

    QApplication a(argc, argv);
    Dialog d;
    d.show();
    return a.exec();
}
