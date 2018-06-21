#include "default_gp_settings.h"

namespace gp_helper {
Button_settings default_gamepad_settings = {
  { gp_buttons::AXIS_LEFT , (int)action_type::MOVE_TRACK},
  { gp_buttons::AXIS_RIGHT , (int)action_type::MOVE_TURRET},
  { gp_buttons::BUT_UP, (int)action_type::MOVE_GUN},
  { gp_buttons::BUT_DOWN, (int)action_type::MOVE_GUN},
  { gp_buttons::BUT_A,   (int)action_type::SHOT }
};
} //namespace gp_helper
