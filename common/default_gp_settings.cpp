#include "default_gp_settings.h"

namespace gp_helper {
Button_settings default_gamepad_settings = {
  { gp_buttons::AXIS_LEFT , (int)action_type::MOVE_TRACK},
  { gp_buttons::BUT_LEFT , (int)action_type::MOVE_TOWER_LEFT},
  { gp_buttons::BUT_RIGHT , (int)action_type::MOVE_TOWER_RIGHT },
  { gp_buttons::BUT_UP, (int)action_type::MOVE_GUN_UP},
  { gp_buttons::BUT_DOWN, (int)action_type::MOVE_GUN_DOWN},
  { gp_buttons::BUT_A,   (int)action_type::SHOT }
};
} //namespace gp_helper
