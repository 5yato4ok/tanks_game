#include "mainwindow.h"
#include <QApplication>
#include "tank.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  //tank::TankMngr tank;
  game::Player_server pl;

  //Here goes a server fun
  return a.exec();
}
