#ifndef TRACK_H
#define TRACK_H
#include "action.h"
#include "stdint.h"
#include "arduino_sender.h"
#include "ui_tanks_server.h"
#include <stdint.h>
//TODO: describe limit
namespace tank {
struct Track_desc {
  int8_t velocity;
  direction up_down;
};

enum class track_move : int32_t {CONTINUE_MOVE,DIRECT_MOVE,ROTATE_MOVE, LAST};

class Track_mngr:public QObject {
  Q_OBJECT
 public:
  Track_mngr(Ui_MainWindow* gui, ArduinoSender& ard_mngr);
  tank_status ManageAction(TankAction& action);
 private:
  Ui_MainWindow* gui;
  ArduinoSender& ard_mngr;
  track_move get_tack_move_kind(const TankAction& action);
  bool is_continue_move(const TankAction& action);
  bool is_rotate_move(const TankAction& action);
  bool is_direct_move(const TankAction& action);

  bool is_left_turn(const TankAction& action);
  bool is_right_turn(const TankAction& action);
  bool is_up_move(const TankAction& action);
  bool is_down_move(const TankAction& action);

  direction get_direction(const TankAction& descr);
  std::string form_arduino_packet(const Track_desc& left_track, 
    const Track_desc& right_track);
  
  int8_t get_delta_velocity(const TankAction& descr);
  int8_t get_common_velocity(const TankAction& descr);
  double current_x;
  double current_y;
  Track_desc current_left_track;
  Track_desc current_right_track;
  const int8_t max_speed = 100;
  const int8_t velocity_step = 1;
};
}//namespace tank

#endif // TRACK_H
