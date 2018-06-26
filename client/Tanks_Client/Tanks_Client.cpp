#include "Tanks_Client.h"
namespace client {
Tanks_Client::Tanks_Client(QWidget *parent) : Player_local(parent) {
  //if (!gamepad.Is_connected()) {
  //  return;
  //}
  ui.setupUi(this);
  Connect_signals();
  gamepad.Listen_Input();
  get_default_buttons_settings();
}

gp_helper::Button_settings Tanks_Client::Init_User_Buttons(gp_helper::Button_settings user_def) {
  auto previos_setting = supported_buttons;
  supported_buttons = user_def;
  return previos_setting;
}
bool Tanks_Client::get_default_buttons_settings() {
  return false;
}
bool Tanks_Client::is_tank_action(Raw_Action& buffer) {
  for (auto& sp_button : supported_buttons) {
    if (sp_button.first == buffer.button) {
      return true;
    }
  }
  return false;
}

void Tanks_Client::ReceiveData(Raw_Action buffer) {
  qDebug() << "Tank: Received Data";
  if (!is_tank_action(buffer)) {
    return;
  }
  if (supported_buttons[buffer.button] == (int)action_type::MOVE_TRACK) {
    qDebug() << "Is track action";
  } else if (supported_buttons[buffer.button] == (int)action_type::MOVE_TOWER_RIGHT||
    supported_buttons[buffer.button] == (int)action_type::MOVE_TOWER_LEFT ||
    supported_buttons[buffer.button] == (int)action_type::MOVE_GUN_UP || 
    supported_buttons[buffer.button] == (int)action_type::MOVE_GUN_DOWN) {
    qDebug() << "Is tower action";
  } else if (supported_buttons[buffer.button] == (int)action_type::SHOT) {
    qDebug() << "Is gun action";
  }
  TankAction action;
  action.type = (action_type)supported_buttons[buffer.button];
  action.x_value = buffer.value_x;
  action.y_value = buffer.value_y;
  Player_local::SendActionsToServer();
  return;
}

void Tanks_Client::Connect_signals() {
  connect(&gamepad, SIGNAL(sendAction(Raw_Action)), this,
    SLOT(ReceiveData(Raw_Action)));
}
void Tanks_Client::Disconnect_signals() {
  disconnect(&gamepad, SIGNAL(sendAction(Raw_Action)), this,
    SLOT(ReceiveData(Raw_Action)));
}
  
}//namespace client
