#include "mainwindow.h"
#include <QApplication>
#include "tank.h"
#include "gamepadmngr.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    GamePadMngr cntrl;
    tank::Tank_mngr tank(cntrl);
    return a.exec();
}
