#ifndef TANK_H
#define TANK_H
#include "body.h"
#include "turret.h"
#include "track.h"
#include "action.h"
#include "gamepadmngr.h"


namespace tank {
class Tank_mngr {
 public:
   explicit Tank_mngr(GamePadMngr& gamepad);
   tank_status WaitForAction();
   tank_status SendActionToMngr(Action& action);
   bool Is_initialized() { return is_intialized_; }
 private:
   GamePadMngr& gamepad;
   Turret_mngr turet;
   Track_mngr track;
   Body_mngr body_mngr;
   bool is_intialized_;
};

} //namespace Tank

#endif // TANK_H
