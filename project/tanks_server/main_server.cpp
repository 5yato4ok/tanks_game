#include <QApplication>
#include "tank.h"
#include "ui_tanks_server.h"
#include <thread>
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QMainWindow window;
  Ui_MainWindow gui;
  gui.setupUi(&window); 
  tank::TankMngr tk(&gui);
  window.showNormal();
  return a.exec();
}
