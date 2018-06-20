#include "tank.h"
namespace tank {
Tank_mngr::Tank_mngr(GamePadMngr& gamepad_) : 
  gamepad(gamepad_), is_intialized_(false) {
  if (!gamepad.Is_connected()) {
    return;
  }
  gamepad.Listen_Input();

}
} //namespace Tank
