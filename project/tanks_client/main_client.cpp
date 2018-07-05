#include "Tanks_Client.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  client::Tanks_Client tclient;
  if (!tclient.Authenticate()) {
    qDebug() << "Authentication Error";
    return 0;
  }
  tclient.ChooseGame();
  if (tclient.Is_initialized()) {
    //now we are sending actions from gamepad to Tank
  }
  tclient.show();
  tclient.Init_User_Buttons(gp_helper::default_gamepad_settings);
  ServerBuffer tmp = { 0 };
  tmp.type = 1;
  TankAction tmp_tk;
  tmp_tk.type = action_type::MOVE_TOWER_LEFT;
  tmp_tk.x_value = 1.234567;
  tmp_tk.y_value = -2.987654;
  memcpy(tmp.tankAction, &tmp_tk, sizeof(TankAction));
  tclient.SendActionsToServer(tmp);
  return a.exec();
}
