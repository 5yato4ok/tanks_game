#include "tank.h"
namespace tank {
TankMngr::TankMngr(Ui_MainWindow* gui_) : 
  is_intialized_(false),Player_server(gui_),tower(gui_),track(gui_) {
  init_receive_port();
  connect(this, SIGNAL(tankDataReceived(TankAction)),SLOT(ReceiveData(TankAction)));
}
void TankMngr::ReceiveData(TankAction buffer) {
  gui->output->appendPlainText("TankMngr Received Data. Switching the type");
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

void TankMngr::init_receive_port() {

}

} //namespace Tank
