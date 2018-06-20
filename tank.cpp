#include "tank.h"
namespace tank {
TankMngr::TankMngr(GamePadMngr* gamepad_, QObject *parent) :
  gamepad(gamepad_), is_intialized_(false) {
  if (!gamepad->Is_connected()) {
    return;
  }
}

void TankMngr::ReceiveData(Action buffer) {
  SendActionToMngr(buffer);
}

void TankMngr::Init_signals() {
  gamepad->Listen_Input();
  connect(gamepad, SIGNAL(GamePadMngr::sendAction(Action)), this, SLOT(TankMngr::ReceiveData(Action)));
}
} //namespace Tank
