#ifndef TURRET_H
#define TURRET_H
#include "gun.h"
#include <QtCore/QObject>
#include "vision.h"
#include "action.h"
#include "stdint.h"
#include "arduino_sender.h"
#include "ui_tanks_server.h"
//TODO: make limit
namespace tank{
class Tower_mngr: QObject {
  Q_OBJECT
 public:
  Tower_mngr(Ui_MainWindow* gui, ArduinoSender& ard_mngr, QObject *parent = nullptr);
  tank_status ManageAction(TankAction& action);
 private:
  Ui_MainWindow* gui;
  ArduinoSender& ard_mngr;
  Gun_mngr gun;
  int32_t cur_rotation_step;
  bool is_action_valid(TankAction & action);
  bool is_step_less_max();
  bool is_step_more_min();
  int32_t update_rotation_step();
  std::string form_arduino_packet(TankAction & action);
  const int32_t max_rotation_step = 600;
  const int32_t min_rotation_step = -600;
};

}//namespace tank

#endif // TURRET_H
