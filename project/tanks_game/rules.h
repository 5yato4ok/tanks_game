#pragma once
#include <stdint.h>
//TODO: make common folder for all headers
#include "default_gp_settings.h"
#include "game_type.h"
struct Rules {
  int32_t number_life;
  int32_t max_players;
  int32_t number_friends;
  int32_t number_enemies;
  gp_helper::Button_settings default_buttons;
};

//extern std::map<game_type,Rules> game_rules;