#pragma once
#include "action.h"
#include <map>


namespace gp_helper {
using Button_settings = std::map<gp_helper::gp_buttons, int32_t>;
extern Button_settings default_gamepad_settings;

} //namespace gp_helper

