#ifndef GUN_H
#define GUN_H
#include <stdint.h>
#include "action.h"
namespace tank {

class Gun_mngr {
 public:
  Gun_mngr();
  tank_status ManageAction(Action& action);
 private:
  tank_status shot();
  tank_status change_height();
  int32_t shoot_num;
  int32_t height;
};

} //namespace tank
#endif // GUN_H
