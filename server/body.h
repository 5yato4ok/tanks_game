#ifndef BODY_H
#define BODY_H
#include "action.h"

//TODO: in future separate to more parts if nedded
namespace tank{

class Body_mngr {
 public:
  Body_mngr();
  tank_status ManageAction(TankAction& action);
};

}//namespace tank
#endif // BODY_H
