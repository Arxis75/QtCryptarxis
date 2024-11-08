#include <UI/dialog.h>
#include <QApplication>

int main(int argc, char *argv[])
{
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