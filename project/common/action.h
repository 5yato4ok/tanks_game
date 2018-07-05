#ifndef ACTION_H
#define ACTION_H
#include <stdint.h>
#include <vector>

//all actions which user can do
enum class action_type : int32_t {MOVE_TOWER_LEFT,MOVE_TOWER_RIGHT,
  MOVE_TRACK,MOVE_GUN_UP,MOVE_GUN_DOWN,WAIT,SHOT,NONE}; //TODO: what else?
//TODO:Which kind of debug signals can be returned

enum class tank_status:int32_t {OPPERATION_SUCCESS,OPERATION_FAILED};
//TODO: What else?
enum class game_status:int32_t {DIED,LOST_LIFE,WIN,SHOT,GET_HIT};

enum class direction :int8_t { UP, DOWN, RIGHT, LEFT ,NONE};

struct TankAction {
  action_type type;
  tank_status result;
  double x_value;
  double y_value;
  bool is_pressed;
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
