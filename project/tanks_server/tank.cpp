#include "tank.h"
namespace tank {
TankMngr::TankMngr( QObject *parent) : is_intialized_(false) {
  init_receive_port();
}
void TankMngr::ReceiveData(TankAction buffer) {
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
