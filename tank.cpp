#include "tank.h"
namespace tank {
TankMngr::TankMngr( QObject *parent) : is_intialized_(false) {
  if (!gamepad.Is_connected()) {
    return;
  }
}

bool TankMngr::is_tank_action(gp_helper::Raw_Action& buffer) {
  return true;
}

bool TankMngr::is_turret_action(gp_helper::Raw_Action& buffer) {
  return true;
}
TankAction TankMngr::get_turret_action(gp_helper::Raw_Action& buffer) {
  TankAction action;
  return action;
}


bool TankMngr::is_body_action(gp_helper::Raw_Action& buffer) {
  return true;
}
TankAction TankMngr::get_body_action(gp_helper::Raw_Action& buffer) {
  TankAction action;
  return action;
}

bool TankMngr::is_track_action(gp_helper::Raw_Action& buffer) {
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

void TankMngr::Init_signals() {
  gamepad.Listen_Input();
  connect(&gamepad, SIGNAL(gp_helper::GamePadMngr::sendAction(gp_helper::Raw_Action)), this,
    SLOT(TankMngr::ReceiveData(gp_helper::Raw_Action)));
}
} //namespace Tank
