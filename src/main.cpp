#include <UI/dialog.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    Integer x = -1;
    x += 1;
    QApplication a(argc, argv);
    Dialog d;
    d.show();
    return a.exec();
}