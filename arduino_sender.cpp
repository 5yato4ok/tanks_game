#include "arduino_sender.h"

std::map<action_type, std::string> command_dict;

ArduinoSender::ArduinoSender() {}

tank_status ArduinoSender::SendAction() {
  return tank_status();
}
