#include "Player_local.h"

namespace client {
Player_local::Player_local(QWidget *parent): QMainWindow(parent), 
user_id(1234), password("pass") {
  choosed_game = game_type::ERROR;
}

void Player_local::ReDrawStreamingVideo() {
  get_streaming_video();
  //and here comes some fun
}

void Player_local::SendActionsToServer() {
  //sending buffer to server
  qDebug() << "Try to send data;";
}

void Player_local::get_streaming_video() {
  //open cv connect by rhtcp
}

void Player_local::ChooseGame(game_type game_type) {
  choosed_game = game_type;
}

bool Player_local::Authenticate(player_type player, controler_type cntrl) {
  //make here checking on which controller and player type
  return true;
}
}