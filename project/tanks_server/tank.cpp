#include "tank.h"
namespace tank {
TankMngr::TankMngr(Ui_MainWindow* gui_) : 
  is_intialized_(false),Player_server(gui_),ard_mngr(gui_),
  tower(gui_,ard_mngr),track(gui_,ard_mngr) {
  //if (init_receive_port()) {
  init_receive_port();
  is_intialized_ = true;
  connect(this, SIGNAL(tankDataReceived(TankAction)), SLOT(ReceiveData(TankAction)));
  
  //}
}

void TankMngr::ReceiveData(TankAction buffer) {
  gui->tank_out->appendPlainText("TankMngr Received Data. Switching the type");
 switch (buffer.type) {
  case action_type::MOVE_GUN_UP:
  case action_type::MOVE_GUN_DOWN:
  case action_type::MOVE_TOWER_LEFT:
  case action_type::MOVE_TOWER_RIGHT:
    tower.ManageAction(buffer);
    break;
  case action_type::MOVE_TRACK:
    track.ManageAction(buffer);
    break;
  }
}

void TankMngr::find_free_steel() {}

bool TankMngr::init_receive_port() {
  find_free_steel();
  return ard_mngr.Init(ip_tank_1, port_in);
}

} //namespace Tank
