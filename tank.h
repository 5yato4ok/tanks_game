#ifndef TANK_H
#define TANK_H
#include "body.h"
#include "turret.h"
#include "track.h"
#include "action.h"


namespace tank {
class Tank_mngr {
 public:
    Tank_mngr();
    tank_status WaitForAction();
    tank_status SendActionToMngr(Action& action);
 private:
    Turret_mngr turet;
    Track_mngr track;
    Body_mngr body_mngr;
};

} //namespace Tank

#endif // TANK_H
