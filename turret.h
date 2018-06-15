#ifndef TURRET_H
#define TURRET_H
#include "gun.h"
#include "vision.h"
#include "action.h"
#include "stdint.h"

namespace tank{
class Turret_mngr {
  public:
    Turret_mngr();
    tank_status ManageAction(Action& action);
  private:
    int32_t rotate();
    Gun_mngr gun;
    Vision_mngr vision;
    int32_t velocity;
    float angle;

};

}//namespace tank

#endif // TURRET_H
