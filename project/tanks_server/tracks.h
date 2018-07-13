#ifndef TRACK_H
#define TRACK_H
#include "action.h"
#include "track.h"
#include "stdint.h"
#include "arduino_sender.h"
#include "ui_tanks_server.h"
#include <stdint.h>
//TODO: describe limit
namespace tank {

enum class track_move : int32_t {CONTINUE_MOVE,DIRECT_MOVE,ROTATE_MOVE, LAST};

class Track_mngr:public QObject {
  Q_OBJECT
 public:
  Track_mngr(Ui_MainWindow* gui, ArduinoSender& ard_mngr);
  tank_status ManageAction(TankAction& action);
 private:
  Ui_MainWindow* gui;
  ArduinoSender& ard_mngr;
  track_move get_track_move_kind(const TankAction& action);
  bool is_left_turn(const TankAction& action);
  bool is_right_turn(const TankAction& action);
  int8_t get_delta_velocity(const TankAction& descr);
  int8_t get_common_velocity(const TankAction& descr);
  direction get_direction(const TankAction& descr);
  Tank_Tracks get_direct_descr(const TankAction& descr);
  Tank_Tracks get_rotate_descr(const TankAction& descr);
  std::string form_arduino_packet(const Tank_Tracks& tracks_descr);
  tank_status send_action_sequence(Tank_Tracks& tracks_descr);
  bool is_first_launch();
  Tank_Tracks current_tracks;
  double current_x;
  double current_y;
  const int8_t max_speed = 100;
  const int8_t velocity_step = 1;
};
}//namespace tank

#endif // TRACK_H
