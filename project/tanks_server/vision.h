#ifndef VISION_H
#define VISION_H
#include "action.h"

namespace tank {

class Vision_mngr {
 public:
    Vision_mngr();
    tank_status ManageAction(TankAction& action);
 private:
  void zoom();
  //here some camera OpenCV class
};
}
#endif // VISION_H
