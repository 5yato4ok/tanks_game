#pragma once
#include "windows.h"
#include "WinSock.h"
#include "action.h"
#include <map>
struct ArduinoPacket {

};

extern std::map<action_type, std::string> command_dict;

class ArduinoSender {
 public:
  ArduinoSender();
  tank_status SendAction();
private:
  void init_socket();
  void check_port();
  void send_buffer_to_port();
};
