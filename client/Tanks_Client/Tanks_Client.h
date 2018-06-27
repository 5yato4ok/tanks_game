#pragma once
#include "Player_local.h"
#include "gamepadmngr.h"

//TODO: Make controller as input
//TODO: make separate gui tank_client or improve this to gui
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
  bool get_default_buttons_settings();
  gp_helper::Button_settings supported_buttons;
  bool is_tank_action(Raw_Action& buffer);
  gp_helper::GamePadMngr gamepad;
  Ui::Tanks_ClientClass ui;
  bool is_intialized_;
};
}//namespace client
