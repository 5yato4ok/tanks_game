#include "tank.h"
namespace tank {
TankMngr::TankMngr( QObject *parent) : is_intialized_(false) {
  if (!gamepad.Is_connected()) {
    return;
  }
  gamepad.Listen_Input();
  init_supported_buttons();
}
void TankMngr::init_supported_buttons() {
  supported_buttons = {
    /*gp_helper::gp_buttons::AXIS_LEFT,*/ gp_helper::gp_buttons::AXIS_RIGHT,
    gp_helper::gp_buttons::BUT_DOWN, gp_helper::gp_buttons::BUT_RIGHT,
    gp_helper::gp_buttons::BUT_UP, gp_helper::gp_buttons::BUT_LEFT
  };
}
bool TankMngr::is_tank_action(gp_helper::Raw_Action& buffer) {
  for (auto& sp_button : supported_buttons) {
    if (sp_button == buffer.button) {
      return true;
    }
  }
  return false;
}

bool TankMngr::is_turret_action(gp_helper::Raw_Action& buffer) {
  if (buffer.button == gp_helper::gp_buttons::BUT_LEFT ||
      buffer.button == gp_helper::gp_buttons::BUT_RIGHT ||
      buffer.button == gp_helper::gp_buttons::BUT_DOWN ||
      buffer.button == gp_helper::gp_buttons::BUT_UP) {
    return true;
  }
  return false;
}
TankAction TankMngr::get_turret_action(gp_helper::Raw_Action& buffer) {
  TankAction action;
  return action;
}


bool TankMngr::is_body_action(gp_helper::Raw_Action& buffer) {
  //maybe put here something for vision. maybe push on button for zooming
  return false;
}
TankAction TankMngr::get_body_action(gp_helper::Raw_Action& buffer) {
  TankAction action;
  return action;
}

bool TankMngr::is_track_action(gp_helper::Raw_Action& buffer) {
  //check left and right axis. check validaty according doc
  if (buffer.button == gp_helper::gp_buttons::AXIS_RIGHT) {
    return true;
  }
  return true;
}
TankAction TankMngr::get_track_action(gp_helper::Raw_Action& buffer) {
  TankAction action;
  return action;
}

void TankMngr::ReceiveData(gp_helper::Raw_Action buffer) {
  qDebug() << "Tank: Received Data";
  if (is_tank_action(buffer)) {
    qDebug() << "Is tank action";
    if (is_track_action(buffer)) {
      qDebug() << "Is track action";
      track.ManageAction(get_track_action(buffer));
    } else if (is_turret_action(buffer)){
      qDebug() << "Is turret action";
      turret.ManageAction(get_track_action(buffer));
    } else if (is_body_action(buffer)) {
      qDebug() << "Is body action";
      body_mngr.ManageAction(get_track_action(buffer));
    }
  }
  return;
}

void TankMngr::Connect_signals() {
  connect(&gamepad, SIGNAL(gp_helper::GamePadMngr::sendAction(gp_helper::Raw_Action)), this,
    SLOT(TankMngr::ReceiveData(gp_helper::Raw_Action)));
}
void TankMngr::Disconnect_signals() {
  disconnect(&gamepad, SIGNAL(gp_helper::GamePadMngr::sendAction(gp_helper::Raw_Action)), this,
    SLOT(TankMngr::ReceiveData(gp_helper::Raw_Action)));
}
} //namespace Tank
