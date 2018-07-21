#include "tracks.h"

namespace tank {
Track_mngr::Track_mngr(Ui_MainWindow* gui_, ArduinoSender& ard_mngr_)
  :gui(gui_),ard_mngr(ard_mngr_) {
  current_tracks.right_track.is_right = true;
  connect(&thread, &TrackThread::send_action, this, &Track_mngr::send_to_arduino);
}

//M000111 Ц управление гусеницами танка, где :
//  1 цифра Ц направление движени€ левой гусеницы(0 - вперед, 1 Ц назад)
//  2 - 3 цифры Ц мощность в процентах от 00 до 99 поданна€ на левую гусеницу танка
//  4 цифра Ц направление движени€ правой гусеницы
//  5 - 6 цифра Ц мощность в процентах правой гусеницы

std::string Track_mngr::form_arduino_packet(const Tank_Tracks& tracks_descr) {
  std::string command = "M" + std::to_string(int(tracks_descr.left_track.up_down));
  if (tracks_descr.left_track.velocity < 10) {
    command += std::to_string(0);
  }
  command += std::to_string(tracks_descr.left_track.velocity) + 
    std::to_string(int(tracks_descr.right_track.up_down));
  if (tracks_descr.right_track.velocity < 10) {
    command += std::to_string(0);
  }
  command += std::to_string(tracks_descr.right_track.velocity);
  return command;
}

bool  Track_mngr::is_reverse_turn(double x, double y) {
  return abs(x) == 1 && !y;
}

Track_desc Track_mngr::get_track_descr(int8_t track_value) {
  Track_desc track;
  if (track_value < 0) {
    track.up_down = direction::DOWN;
    track.velocity = track_value * (-1);
  } else {
    track.up_down = direction::UP;
    track.velocity = track_value;
  }
  return track;
}

Tank_Tracks Track_mngr::get_tracks_descr(const TankAction& action) {
  int8_t x = action.x_value * 100;
  int8_t y = action.y_value * 100;
  if (is_reverse_turn(action.x_value, action.y_value)) {
    x = x * (-1);
  }
  int8_t V = (100 - abs(x)) * (y / 100) + y; // R+L
  int8_t W = (100 - abs(y)) * (x / 100) + x; //R-L
  int8_t right_track = (V + W) / 2;
  int8_t left_track = (V - W) / 2;
  Tank_Tracks result;
  result.left_track = get_track_descr(left_track);
  result.right_track = get_track_descr(right_track);
  result.right_track.is_right = true;
  return result;
}
bool Track_mngr::is_first_launch() {
  return current_tracks.left_track.velocity == 0 && 
    current_tracks.right_track.velocity == 0;
}

void Track_mngr::send_to_arduino(Tank_Tracks tracks_descr) {
  ard_mngr.SendAction(form_arduino_packet(tracks_descr));
  update_tracks(tracks_descr);
}

void Track_mngr::update_tracks(Tank_Tracks& tracks_descr) {
  current_tracks = tracks_descr;
}

tank_status Track_mngr::ManageAction(TankAction& action) {
  Tank_Tracks tracks_descr = get_tracks_descr(action);
  thread.Exit();
  thread.SetPacket(current_tracks,tracks_descr);
  thread.Start();
  return tank_status::OPPERATION_SUCCESS;
}

}//namespace tank
