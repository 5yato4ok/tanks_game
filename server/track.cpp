#include "track.h"

namespace tank {
Track_mngr::Track_mngr() {

}

tank_status Track_mngr::ManageAction(TankAction & action) {
  get_direction(action.x_value, action.y_value);
  get_velocity(action.x_value, action.y_value);
  return tank_status();
}
void Track_mngr::get_direction(double value_x, double value_y) {
}

int32_t Track_mngr::get_velocity(double value_x, double value_y) {
  return int32_t();
}
}//namespace tank
