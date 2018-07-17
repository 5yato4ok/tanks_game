#pragma once
#include "action.h"
#include <QDataStream>
//type:
// 1- tank_action //TODO: make enum
// 2 - camera_url
// 3 - game_buffer
//

enum class msg_type :int {TANK_ACTION, CAMERA_URL, GAME_BUFFER, LAST};

struct ServerBuffer {
  int type;
  int size;
  char tankAction[1024];
};

QDataStream &operator <<(QDataStream &out, const ServerBuffer& dataStruct);
QDataStream &operator >> (QDataStream &in, ServerBuffer& dataStruct);