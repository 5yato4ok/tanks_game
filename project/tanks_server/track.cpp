#include "track.h"

namespace tank {
Track_mngr::Track_mngr(Ui_MainWindow* gui_, ArduinoSender& ard_mngr_)
  :gui(gui_),ard_mngr(ard_mngr_) {
  current_x = 0;
  current_y = 0;
}

std::string Track_mngr::form_arduino_packet(const Track_desc& left_track,
  const Track_desc& right_track) {
  return std::string();
}
//M000111 Ц управление гусеницами танка, где :
//  1 цифра Ц направление движени€ левой гусеницы(0 - вперед, 1 Ц назад)
//  2 - 3 цифры Ц мощность в процентах от 00 до 99 поданна€ на левую гусеницу танка
//  4 цифра Ц направление движени€ правой гусеницы
//  5 - 6 цифра Ц мощность в процентах правой гусеницы

bool Track_mngr::is_left_turn(const TankAction& action) {
  return true;
}

bool Track_mngr::is_right_turn(const TankAction& action) {
  return false;
}

tank_status Track_mngr::ManageAction(TankAction& action) {
  Track_desc descr_left;
  Track_desc descr_right;
  switch (get_track_move_kind(action)) {
  case track_move::CONTINUE_MOVE : { 
    break; 
  }
  case track_move::DIRECT_MOVE: { 
    break; 
  }
  case track_move::ROTATE_MOVE: { 
    break; 
  }
  default:
    return tank_status::OPERATION_FAILED;
  }
  ard_mngr.SendAction(form_arduino_packet(descr_left,descr_right));
  return tank_status();
}

direction Track_mngr::get_direction(const TankAction& descr) {
  return (descr.y_value < current_y) ? direction::DOWN : direction::UP;
}

int8_t get_common_velocity(const TankAction& descr) {
  return int8_t();
}

int8_t Track_mngr::get_delta_velocity(const TankAction& descr) {

  return int8_t();
}
}//namespace tank
