#include "gun.h"

namespace tank {
Gun_mngr::Gun_mngr(Ui_MainWindow* gui_, QHostAddress steel_ip,
  quint16 steel_port):gui(gui_),ard_mngr(gui_, QHostAddress::Any, 34005) {
  cur_rotation = 0;
  max_rotation = 48;
  min_rotation = -48;
}

void Gun_mngr::Init_arduino(const QHostAddress& ip, quint16 steel_port) {
  ard_mngr.Init(ip, steel_port);
}

tank_status Gun_mngr::ManageAction(TankAction & action) {
  switch (action.type) {
  case action_type::SHOT:
    return ard_mngr.SendAction(std::string("S"));
  case action_type::MOVE_GUN_UP:
  case action_type::MOVE_GUN_DOWN:
    //check here all constants
    if (is_action_valid(action)) {
      return ard_mngr.SendAction(form_arduino_packet(action));
    }
  default:
    break;
  }
}

std::string Gun_mngr::form_arduino_packet(TankAction & action) {
  
  switch (action.type) {
  case action_type::MOVE_GUN_DOWN:
    cur_rotation -= 2;
    break;
  case action_type::MOVE_GUN_UP:
    cur_rotation += 2;
    break;
  default:
    break;
  }
  std::string tower_packet = "G0" + std::to_string(cur_rotation);
  return tower_packet;
}

bool Gun_mngr::is_step_less_max() {
  return cur_rotation < max_rotation;
}
bool Gun_mngr::is_step_more_min() {
  return cur_rotation > min_rotation;
}

bool Gun_mngr::is_action_valid(TankAction & action) {
  return is_step_less_max() && is_step_more_min();
}

}

