#include "tracks.h"

namespace tank {
Track_mngr::Track_mngr(Ui_MainWindow* gui_, ArduinoSender& ard_mngr_)
  :gui(gui_),ard_mngr(ard_mngr_) {
  current_x = 0;
  current_y = 0;
  current_tracks.right_track.is_right = true;
}

//M000111 Ц управление гусеницами танка, где :
//  1 цифра Ц направление движени€ левой гусеницы(0 - вперед, 1 Ц назад)
//  2 - 3 цифры Ц мощность в процентах от 00 до 99 поданна€ на левую гусеницу танка
//  4 цифра Ц направление движени€ правой гусеницы
//  5 - 6 цифра Ц мощность в процентах правой гусеницы

std::string Track_mngr::form_arduino_packet(const Tank_Tracks& tracks_descr) {
  std::string command = "M" + std::to_string(int(tracks_descr.left_track.up_down)) +
    std::to_string(tracks_descr.left_track.velocity) +
    std::to_string(int(tracks_descr.right_track.up_down)) +
    std::to_string(tracks_descr.right_track.velocity);
  return command;
}

int8_t Track_mngr::get_delta_velocity(const TankAction& descr) {
  return int8_t();
}

Tank_Tracks Track_mngr::get_rotate_descr(const TankAction& descr) {
  return Tank_Tracks();
}

bool Track_mngr::is_left_turn(const TankAction& action) {
  return action.x_value< current_x;
}

bool Track_mngr::is_right_turn(const TankAction& action) {
  return action.x_value > current_x;
}

track_move Track_mngr::get_track_move_kind(const TankAction& action) {
  track_move result = track_move::ROTATE_MOVE;
  if (action.x_value == current_x && action.y_value == current_y) {
    return track_move::CONTINUE_MOVE;
  } else if (!action.x_value && action.y_value ||
    !action.y_value && action.x_value) {
    return track_move::DIRECT_MOVE;
  }
  return result;
}

bool Track_mngr::is_first_launch() {
  return current_tracks.left_track.velocity == 0 && 
    current_tracks.right_track.velocity == 0;
}

tank_status Track_mngr::send_action_sequence(Tank_Tracks& tracks_descr) {
  Track_desc max_track;
  Track_desc min_track;
  tank_status result;
  if (tracks_descr.left_track == tracks_descr.right_track) {
    max_track = min_track = tracks_descr.left_track;
  } else if (tracks_descr.left_track < tracks_descr.right_track) {
    max_track = tracks_descr.right_track;
    min_track = tracks_descr.left_track;
  } else {
    max_track = tracks_descr.left_track;
    min_track = tracks_descr.right_track;
  }
  for (int i = 0; i < max_track.velocity; i++) {
    Tank_Tracks tmp_descr;
    tmp_descr.left_track.up_down = tracks_descr.left_track.up_down;
    tmp_descr.right_track.up_down = tracks_descr.right_track.up_down;
    if (max_track.is_right) {
      tmp_descr.right_track.velocity = i;
    } else {
      tmp_descr.left_track.velocity = i;
    }
    if (min_track.is_right && tmp_descr.right_track < min_track) {
      tmp_descr.right_track.velocity = i;
    } else if (!min_track.is_right && tmp_descr.right_track < min_track){
      tmp_descr.left_track.velocity = i;
    }
    result = ard_mngr.SendAction(form_arduino_packet(tracks_descr));
  }
  return result;
}

int8_t Track_mngr::get_common_velocity(const TankAction& descr) {
  double vector_size = sqrt(descr.x_value*descr.x_value + descr.y_value*descr.y_value);
  int8_t velocity = vector_size * 99;
  return velocity;
}

Tank_Tracks Track_mngr::get_direct_descr(const TankAction& descr) {
  Tank_Tracks tracks_descr;
  tracks_descr.left_track.velocity = get_common_velocity(descr);
  tracks_descr.left_track.up_down = get_direction(descr);
  tracks_descr.right_track = tracks_descr.left_track;
  return tracks_descr;
}

tank_status Track_mngr::ManageAction(TankAction& action) {
  Tank_Tracks tracks_descr;
  switch (get_track_move_kind(action)) {
  case track_move::CONTINUE_MOVE:
    tracks_descr = current_tracks;
    break;
  case track_move::DIRECT_MOVE:
    tracks_descr = get_direct_descr(action);
    break;
  case track_move::ROTATE_MOVE:
    tracks_descr = get_rotate_descr(action);
    break;
  default:
    return tank_status::OPERATION_FAILED;
  }
  if (!is_first_launch()) {
    return ard_mngr.SendAction(form_arduino_packet(tracks_descr));
  } 
  return send_action_sequence(tracks_descr);
}

direction Track_mngr::get_direction(const TankAction& descr) {
  return (descr.y_value < current_y) ? direction::DOWN : direction::UP;
}

}//namespace tank
