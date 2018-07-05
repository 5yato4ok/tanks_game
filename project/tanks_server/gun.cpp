#include "gun.h"

namespace tank {
Gun_mngr::Gun_mngr(Ui_MainWindow* gui_, QHostAddress steel_ip,
  quint16 steel_port):gui(gui_){

}

tank_status Gun_mngr::ManageAction(TankAction & action) {
  return tank_status();
}

}

