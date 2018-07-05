#include "tank.h"
namespace tank {
TankMngr::TankMngr(Ui_MainWindow* gui_) : 
  is_intialized_(false),Player_server(gui_),tower(gui_),track(gui_) {
  init_receive_port();
  connect(this, SIGNAL(tankDataReceived(TankAction)),SLOT(ReceiveData(TankAction)));
}
void TankMngr::ReceiveData(TankAction buffer) {
  gui->tank_out->appendPlainText("TankMngr Received Data. Switching the type");
 switch (buffer.type) {
  case action_type::MOVE_GUN_UP:
  case action_type::MOVE_GUN_DOWN:
  case action_type::MOVE_TOWER_LEFT:
  case action_type::MOVE_TOWER_RIGHT:
    tower.ManageAction(buffer);
  case action_type::MOVE_TRACK:
    track.ManageAction(buffer);
  }
}

void TankMngr::find_free_steel() {}

void TankMngr::init_receive_port() {
  find_free_steel();
  tower.Init_arduino(ip_tank_0, port_in);
}

} //namespace Tank
