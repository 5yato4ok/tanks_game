#include "gun.h"

namespace tank {
Gun_mngr::Gun_mngr(Ui_MainWindow* gui_, ArduinoSender& ard_mngr_):
  gui(gui_),ard_mngr(ard_mngr_) {
  cur_rotation = 0;
  max_rotation = 90;
  min_rotation = 0;
}

void Gun_mngr::Reset() {
  gui->tank_out->appendPlainText("Gun manager:\n Reseting tank");
  cur_rotation = 0;
  TankAction action;
  std::string null_gun = "G00";
  ard_mngr.SendAction(null_gun);
}

tank_status Gun_mngr::ManageAction(TankAction & action) {
  switch (action.type) {
  case action_type::SHOT:
    return ard_mngr.SendAction(std::string("S"));
  case action_type::MOVE_GUN_UP:
  case action_type::MOVE_GUN_DOWN:
  {
    //QEventLoop loop;
    //QTimer::singleShot(10, &loop, SLOT(quit()));
    //loop.exec();
    if (is_action_valid(action)) {
      return ard_mngr.SendAction(form_arduino_packet(action));
    }
    gui->tank_out->appendPlainText("Gun Mngr: invalid action. Limit is reached.");
  }
  default:
    break;
  }
  return tank_status::OPERATION_FAILED;
}

std::string Gun_mngr::form_arduino_packet(TankAction & action) {
  
  switch (action.type) {
  case action_type::MOVE_GUN_DOWN:
    cur_rotation -= 7;
    break;
  case action_type::MOVE_GUN_UP:
    cur_rotation += 7;
    break;
  default:
    break;
  }
  gui->tank_out->appendPlainText("Tower manager: cur_rotation:" + QString::number(cur_rotation));
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
  if (action.type == action_type::MOVE_GUN_DOWN) {
    return is_step_more_min();
  }
  return is_step_less_max();
}

}

