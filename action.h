#ifndef ACTION_H
#define ACTION_H
#include <stdint.h>

enum class action_type:int32_t {MOVE,SHOT,ROTATE, WAIT,GET_HIT}; //TODO: what else?
//TODO:Which kind of debug signals can be returned
enum class tank_status:int32_t {OPPERATION_SUCCESS,OPERATION_FAILED};
//TODO: What else?
enum class game_status:int32_t {DIED,LOST_LIFE,WIN};

struct Action {
  action_type type;
  tank_status result;
  double double_value;
  std::vector<uintptr_t> additional_buffer;
};

#endif // ACTION_H
