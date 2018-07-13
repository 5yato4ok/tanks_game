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

enum class direction :int8_t { UP = 0, DOWN = 1, RIGHT = 2, LEFT = 3,NONE = 4};

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
namespace gp_helper {
  enum class gp_buttons :int32_t {
    BUT_A, BUT_X, BUT_Y, BUT_B, BUT_L1, BUT_L2,
    BUT_R1, BUT_R2, BUT_SELECT, BUT_GUIDE, BUT_START,
    AXIS_LEFT, AXIS_RIGHT, BUT_UP, BUT_DOWN, BUT_RIGHT, BUT_LEFT
  }; //TODO: what else?
}
struct Raw_Action {
  gp_helper::gp_buttons button;
  double value_x;
  double value_y;
  bool is_pressed;
};


#endif // ACTION_H
