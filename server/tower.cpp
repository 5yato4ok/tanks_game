#include "tower.h"
namespace tank{
Tower_mngr::Tower_mngr(QObject *parent){
  cur_rotation_step = update_rotation_step();
}

int8_t Tower_mngr::update_rotation_step() {
  //form buffer with command give info about cur rotation
  //send it to arduino
  return 0;
}

void Tower_mngr::form_arduino_packet(TankAction & action) {

}

tank_status Tower_mngr::ManageAction(TankAction & action)  {
  tank_status result = tank_status::OPERATION_FAILED;
  if (action.type == action_type::MOVE_GUN_UP ||
    action.type == action_type::MOVE_GUN_DOWN) {
    return gun.ManageAction(action);
  }
  if (!is_action_valid(action))
    return result;
  form_arduino_packet(action);
  ard_mngr.SendAction();
  return result;
}

bool Tower_mngr::is_step_less_max() {
  return cur_rotation_step < max_rotation_step;
}
bool Tower_mngr::is_step_more_min() {
  return cur_rotation_step > min_rotation_step;
}

bool Tower_mngr::is_action_valid(TankAction & action) {
  return is_step_less_max() && is_step_more_min();
}
}
