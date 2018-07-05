#include "vision.h"
namespace tank {

Vision_mngr::Vision_mngr(Ui_MainWindow* gui_): gui(gui_){

}
tank_status Vision_mngr::ManageAction(TankAction & action) {
  return tank_status();
}
}
