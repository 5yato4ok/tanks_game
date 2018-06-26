#pragma once
#include "rules.h"
#include "game_type.h"
#include <vector>

namespace server {
class Game {
public:
  explicit Game(game_type type);
  void Manage_P2P_Action();
private:
  void set_rules(game_type type);
  int32_t get_players_id();
  Rules game_rules;
  std::vector<int32_t> intialized_players;
};
}//namespace server

