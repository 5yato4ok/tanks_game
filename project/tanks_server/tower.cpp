#include "tower.h"
namespace tank{
Tower_mngr::Tower_mngr(Ui_MainWindow* gui_, ArduinoSender& ard_mngr_,QObject *parent):
  gui(gui_),gun(gui_,ard_mngr_),ard_mngr(ard_mngr_) {
  cur_rotation_step = update_rotation_step();
}

int32_t Tower_mngr::update_rotation_step() {
  //form buffer with command give info about cur rotation
  //send it to arduino
  return 0;
}

//H010 Ц управление башней танка, 
//где 1 цифра это направление движени€ (0-вправо, 1-влево), 
//2 и 3 цифры количество щагов необходимое сделать за один раз от 00 до 99
std::string Tower_mngr::form_arduino_packet(TankAction & action) {
  std::string tower_packet;
  switch (action.type) {
    case action_type::MOVE_TOWER_LEFT:
      tower_packet = "H125";
      cur_rotation_step -= 25;
      break;
    case action_type::MOVE_TOWER_RIGHT:
      tower_packet = "H025";
      cur_rotation_step += 25;
      break;
    default:
      break;
  }
  gui->tank_out->appendPlainText("Tower manager: cur_rotation:" + QString::number(cur_rotation_step));
  return tower_packet;
  
}

tank_status Tower_mngr::ManageAction(TankAction & action)  {
  tank_status result = tank_status::OPERATION_FAILED;
  if (action.type == action_type::MOVE_GUN_UP ||
    action.type == action_type::MOVE_GUN_DOWN || action.type == action_type::SHOT) {
    return gun.ManageAction(action);
  }

  if (is_action_valid(action)) {
    result = ard_mngr.SendAction(form_arduino_packet(action));
  } else if (!is_step_less_max()){
    gui->tank_out->appendPlainText("Tower manager:\n Max limit. Turn to left");
  } else if (!is_step_more_min()) {
    gui->tank_out->appendPlainText("Tower manager:\n Min limit. Turn to right");
  }
  if (result == tank_status::OPERATION_FAILED) {
    gui->tank_out->appendPlainText("Tower manager:\n Sending action error");
  }
  gui->centralWidget->update();
  return result;
}

bool Tower_mngr::is_step_less_max() {
  return cur_rotation_step < max_rotation_step;
}
bool Tower_mngr::is_step_more_min() {
  return cur_rotation_step > min_rotation_step;
}

bool Tower_mngr::is_action_valid(TankAction & action) {
  if (action.type == action_type::MOVE_TOWER_LEFT) {
    return is_step_more_min();
  }
  return is_step_less_max();
}
}
