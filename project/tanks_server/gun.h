#ifndef GUN_H
#define GUN_H
#include <stdint.h>
#include "action.h"
#include "arduino_sender.h"
#include "ui_tanks_server.h"
#include "qtimer.h"

namespace tank {
//TODO: Add wait time
class Gun_mngr {
 public:
  Gun_mngr(Ui_MainWindow* gui, QHostAddress steel_ip = QHostAddress::Any, 
    quint16 steel_port = 34005);
  tank_status ManageAction(TankAction& action);
  void Init_arduino(const QHostAddress& ip, quint16 steel_port);
 private:
  bool is_action_valid(TankAction & action);
  bool is_step_less_max();
  bool is_step_more_min();
  Ui_MainWindow* gui;
  ArduinoSender ard_mngr;
  std::string form_arduino_packet(TankAction & action);
  int32_t shoot_num;
  int32_t cur_rotation; 
  int32_t max_rotation;
  int32_t min_rotation;
};

} //namespace tank
#endif // GUN_H
