#include "maincircuito.h"
#include <QApplication>
#include "circuito_STL.h"

Circuito C;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainCircuito w;
    w.show();

    return a.exec();
}
