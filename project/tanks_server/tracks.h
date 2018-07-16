#ifndef TRACK_H
#define TRACK_H
#include "action.h"
#include "track.h"
#include "stdint.h"
#include "arduino_sender.h"
#include "ui_tanks_server.h"
#include "track_thread.h"
#include <stdint.h>
//TODO: describe limit
namespace tank {

enum class track_move : int32_t {CONTINUE_MOVE,DIRECT_MOVE,ROTATE_MOVE, LAST};

class Track_mngr:public QObject {
  Q_OBJECT
 public:
  Track_mngr(Ui_MainWindow* gui, ArduinoSender& ard_mngr);
  tank_status ManageAction(TankAction& action);
 public slots:
  void send_to_arduino(Tank_Tracks& tracks_descr);
  void update_tracks(Tank_Tracks& tracks_descr);
 private:
  Ui_MainWindow* gui;
  TrackThread thread;
  ArduinoSender& ard_mngr;
  Tank_Tracks get_tracks_descr(const TankAction& action);
  Track_desc get_track_descr(int8_t track_value);
  std::string form_arduino_packet(const Tank_Tracks& tracks_descr);
  tank_status send_action_sequence(Tank_Tracks& tracks_descr);
  bool is_first_launch();
  Tank_Tracks current_tracks;
  const int8_t max_speed = 99;
  const int8_t velocity_step = 1;
};
}//namespace tank

#endif // TRACK_H
