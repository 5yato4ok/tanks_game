#include <QApplication>
#include "tank.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  //tank::TankMngr tank;
  tank::TankMngr tk;
  tk.showNormal();
  //Here goes a server fun
  return a.exec();
}
