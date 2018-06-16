#include "mainwindow.h"
#include <QApplication>
#include "gamepadmngr.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    GamePadMngr cntrl;
    return a.exec();
}
