#include "mainwindow.h"
#include <QApplication>
#include "tank.h"
#include "gamepadmngr.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    tank::TankMngr tank;
    if (tank.Is_initialized()) {
      tank.Init_signals();
    }
    return a.exec();
}
