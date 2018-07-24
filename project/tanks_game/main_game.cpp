#include "tanks_game.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tanks_game w;
    w.show();
    return a.exec();
}
