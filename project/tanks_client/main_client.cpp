#include "Tanks_Client.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  client::Tanks_Client tclient;
  tclient.ChooseGame();
  if (tclient.Is_initialized()) {
    //now we are sending actions from gamepad to Tank
  }
  tclient.Init_User_Buttons(gp_helper::default_gamepad_settings);
  tclient.show();
  
  return a.exec();
}
