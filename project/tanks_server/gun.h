#ifndef GUN_H
#define GUN_H
#include <stdint.h>
#include "action.h"
#include "arduino_sender.h"
#include "ui_tanks_server.h"
namespace tank {
//TODO: set limits
class Gun_mngr {
 public:
  Gun_mngr(Ui_MainWindow* gui, QHostAddress steel_ip = QHostAddress::Any, 
    quint16 steel_port = 34005);
  tank_status ManageAction(TankAction& action);
 private:
  Ui_MainWindow* gui;
  tank_status shot();
  tank_status change_height();
  int32_t shoot_num;
  int32_t cur_rotation;
  int32_t max_rotation;
  int32_t min_rotation;
};

} //namespace tank
#endif // GUN_H
