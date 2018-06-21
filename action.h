#ifndef ACTION_H
#define ACTION_H
#include <stdint.h>
#include <vector>
#include "default_gp_settings.h"
//all actions which user can do
enum class action_type : int32_t {MOVE_TURRET,MOVE_TRACK,
  MOVE_GUN,ROTATE, WAIT,SHOT}; //TODO: what else?
//TODO:Which kind of debug signals can be returned

enum class tank_status:int32_t {OPPERATION_SUCCESS,OPERATION_FAILED};
//TODO: What else?
enum class game_status:int32_t {DIED,LOST_LIFE,WIN,SHOT,GET_HIT};

struct TankAction {
  action_type type;
  tank_status result;
  double double_value;
  std::vector<uintptr_t> additional_buffer;
};

struct InterfaceAction {
  //here additional user actions(game, interface, etc) 
};

struct Action {
  TankAction tank_action;
  InterfaceAction interface_action;
};



#endif // ACTION_H
