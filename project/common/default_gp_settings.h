#pragma once
#include <map>
#include "action.h"

namespace gp_helper {
enum class gp_buttons :int32_t {
  BUT_A, BUT_X, BUT_Y, BUT_B, BUT_L1, BUT_L2,
  BUT_R1, BUT_R2, BUT_SELECT, BUT_GUIDE, BUT_START,
  AXIS_LEFT, AXIS_RIGHT,BUT_UP,BUT_DOWN,BUT_RIGHT,BUT_LEFT
}; //TODO: what else?
using Button_settings = std::map<gp_helper::gp_buttons, int32_t>;
extern Button_settings default_gamepad_settings;

} //namespace gp_helper

