#pragma once
#include "action.h"
#include <QDataStream>
#include <QHostAddress>

enum class msg_type :int {TANK_ACTION, CAMERA_URL, GAME_BUFFER,GAME_RESPONCE, GAME_INIT,GAME_OVER, LAST};
enum class msg_type_ard : int { GAME_ACTION = 0, TANK_INFO = 1, LAST };
enum class tank_info_ard : int { TOWER_INFO = 0, TRACK_INFO = 1, GUN_INFO = 2, LAST };
enum class game_action : int { MAIN_HIT = 0, TRACK_HIT = 1, TOWER_HIT = 2, LAST }; //smth else later

struct Tower_Info {
  int current_step;
};

struct Gun_Info {
  int current_rot;
};

struct Track_Info {
  int left_velocity;
  int left_direction;
  int right_velocity;
  int right_direction;
};

struct Tank_Info {
  int size;
  tank_info_ard info_type; // у себя просто int пиши
  char data[512];
};

//struct ArduinoBuffer {
//  int size;
//  int msg_type; // у себя просто int пиши
//  char data[1024];
//};

struct ArduinoBuffer {
  int type;
};

struct ServerBuffer {
  msg_type type;
  int size;
  char sender[256];
  char tankAction[1024];
};
QByteArray IntToArray(qint32 source);
qint32 ArrayToInt(QByteArray source);
QDataStream &operator <<(QDataStream &out, const ServerBuffer& dataStruct);
QDataStream &operator >> (QDataStream &in, ServerBuffer& dataStruct);