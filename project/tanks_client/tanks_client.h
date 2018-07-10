#pragma once
#include "Player_local.h"
#include "gamepadmngr.h"
#include "ui_tanks_client.h"
#include <QEventLoop>
//TODO: Make controller as input
//TODO: make separate gui tank_client or improve this to gui
//TODO: make button to ping server
namespace client {
  //Tank controlled by GamePad for now
class Tanks_Client : public Player_local {
  Q_OBJECT
 public:
  Tanks_Client(QWidget *parent = Q_NULLPTR);
  void Connect_signals();
  void Disconnect_signals();
  bool Is_initialized() { return is_intialized_; }
  gp_helper::Button_settings Init_User_Buttons(gp_helper::Button_settings user_def);
 public slots:
  void ReceiveData(Raw_Action buffer);  
 private:
   void stop_stub() {};
  void send_action(TankAction buffer);
  bool get_default_buttons_settings();
  gp_helper::Button_settings supported_buttons;
  bool is_tank_action(Raw_Action& buffer);
  gp_helper::GamePadMngr gamepad;
  Ui::Tanks_ClientClass* ui;
  bool is_intialized_;
};
}//namespace client
