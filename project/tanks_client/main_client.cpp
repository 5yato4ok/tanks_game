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
  //ServerBuffer tmp = { 0 };
  //tmp.type = 1;
  //TankAction tmp_tk;
  //tmp_tk.type = action_type::MOVE_TOWER_LEFT;
  //tmp_tk.x_value = 1.234567;
  //tmp_tk.y_value = -2.987654;
  //tmp_tk.is_pressed = true;
  //memcpy(tmp.tankAction, &tmp_tk, sizeof(TankAction));
  //QTimer time;
  //for (int i = 0; i < 10; i++) {
  //  tclient.SendActionsToServer(tmp);
  //  time.start(100);
  //}
  //ServerBuffer tmp2 = { 0 };
  //TankAction tmp_tk2;
  //tmp_tk2.type = action_type::SHOT;
  //memcpy(tmp2.tankAction, &tmp_tk2, sizeof(TankAction));
  //tclient.SendActionsToServer(tmp2);
  //time.start(100);
  //ServerBuffer tmp3 = { 0 };
  //TankAction tmp_tk3;
  //tmp_tk2.type = action_type::MOVE_GUN_UP;
  //memcpy(tmp3.tankAction, &tmp_tk3, sizeof(TankAction));
  //tclient.SendActionsToServer(tmp3);
  //time.start(100);
  return a.exec();
}
