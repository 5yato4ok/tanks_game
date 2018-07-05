#include "gun.h"

namespace tank {
Gun_mngr::Gun_mngr(Ui_MainWindow* gui_):gui(gui_){

}

tank_status Gun_mngr::ManageAction(TankAction & action) {
  return tank_status();
}

}

