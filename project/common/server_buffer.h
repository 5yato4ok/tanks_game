#pragma once
#include "action.h"
#include <QDataStream>
#include <QHostAddress>

enum class msg_type :int {TANK_ACTION, CAMERA_URL, GAME_BUFFER, LAST};

struct ServerBuffer {
  msg_type type;
  int size;
  char sender[256];
  char tankAction[1024];
};

QDataStream &operator <<(QDataStream &out, const ServerBuffer& dataStruct);
QDataStream &operator >> (QDataStream &in, ServerBuffer& dataStruct);