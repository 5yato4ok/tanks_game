#include <QApplication>
#include "tank.h"
#include "ui_tanks_server.h"
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  //tank::TankMngr tank;
  QMainWindow window;
  Ui_MainWindow gui;
  gui.setupUi(&window);
  tank::TankMngr tk(&gui);
  window.showNormal();
  //Here goes a server fun
  return a.exec();
}