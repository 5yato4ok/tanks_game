#ifndef TURRET_H
#define TURRET_H
#include "gun.h"
#include <QtCore/QObject>
#include "vision.h"
#include "action.h"
#include "stdint.h"
#include "arduino_sender.h"

//TODO: make limit
namespace tank{
class Tower_mngr: QObject {
  Q_OBJECT
 public:
  Tower_mngr(QObject *parent = nullptr);
  tank_status ManageAction(TankAction& action);
 private:
  Gun_mngr gun;
  Vision_mngr vision;
  ArduinoSender ard_mngr;
  int8_t cur_rotation_step;
  bool is_action_valid(TankAction & action);
  bool is_step_less_max();
  bool is_step_more_min();
  int8_t update_rotation_step();
  void form_arduino_packet(TankAction & action);
  const int8_t max_rotation_step = 300;
  const int8_t min_rotation_step = -300;
};

}//namespace tank

#endif // TURRET_H