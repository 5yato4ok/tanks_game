#pragma once
#include "action.h"

//type:
// 1- tank_action //TODO: make enum
//
struct ServerBuffer {
  int type;
  int size;
  char tankAction[1024];
};
