#include <QApplication>
#include "tank.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  //tank::TankMngr tank;
  game::Player_server pl;
  pl.show();
  //Here goes a server fun
  return a.exec();
}
