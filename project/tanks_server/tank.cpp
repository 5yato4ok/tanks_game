#include "tank.h"
namespace tank {
TankMngr::TankMngr(Ui_MainWindow* gui_) : 
 is_intialized_(false),Player_server(gui_),ard_mngr(gui_),
 tower(gui_,ard_mngr),track(gui_,ard_mngr) {
  connect(this, &Player_server::server_started, this, &TankMngr::init_receive_port);
  connect(this, SIGNAL(tankDataReceived(TankAction)), SLOT(ReceiveData(TankAction)));
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

void TankMngr::init_receive_port(int32_t tank_id) {
  switch (tank_id) {
  case g_server_port_1:
    is_intialized_ = ard_mngr.Init(ip_tank_1, port_in);
    break;
  case g_server_port_2:
    is_intialized_ = ard_mngr.Init(ip_tank_2, port_in);
    break;
  case g_server_port_3:
    is_intialized_ = ard_mngr.Init(ip_tank_3, port_in);
    break;
  default:
    is_intialized_ = false;
    return;
  }
  
}

} //namespace Tank
