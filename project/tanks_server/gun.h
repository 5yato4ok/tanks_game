#ifndef GUN_H
#define GUN_H
#include <stdint.h>
#include "action.h"
#include "ui_tanks_server.h"
namespace tank {
//TODO: set limits
class Gun_mngr {
 public:
  explicit Gun_mngr(Ui_MainWindow* gui);
  tank_status ManageAction(TankAction& action);
 private:
  Ui_MainWindow* gui;
  tank_status shot();
  tank_status change_height();
  int32_t shoot_num;
  int32_t height;
};

} //namespace tank
#endif // GUN_H
