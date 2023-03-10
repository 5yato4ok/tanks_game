#pragma once
#include "Player_local.h"
#include "gamepadmngr.h"
#include "ui_tanks_client.h"
#include <QEventLoop>
#include "camera.h"
#include "timer_thread.h"
#include "QSoundEffect"
#include "QPicture"
#include "server_settings.h"
//TODO: Make controller as input
//TODO: make separate gui tank_client or improve this to gui
//TODO: make button to ping server
namespace client {
  //Tank controlled by GamePad for now
class Tanks_Client : public Player_local {
  Q_OBJECT
 public:
  void resizeEvent(QResizeEvent* event);
  Tanks_Client(QMainWindow *parent = Q_NULLPTR);
  void Disconnect_signals();
  bool Is_initialized() { return is_intialized_; }
  gp_helper::Button_settings Init_User_Buttons(gp_helper::Button_settings user_def);
 public slots:
  void Connect_signals();
  void ReceiveData(Raw_Action buffer);
  void load_video();
  void start_video();
  void reconnect();
  void change_hp(Player_condition current_condition);
  void game_over(Player_condition current_condition);
  void change_can_shot();
  void show_debug_window();
 private:
  void set_gui();
  void start_shot_timer();
  void Tanks_Client::enable_reconnect_button();
  void send_action(TankAction buffer);
  bool get_default_buttons_settings();
  gp_helper::Button_settings supported_buttons;
  bool is_tank_action(Raw_Action& buffer);
  gp_helper::GamePadMngr gamepad;
  Ui::Tanks_ClientClass* ui;
  bool is_intialized_;
  Camera camera;
  bool can_shoot;
  TimerThread timer;
  QSoundEffect gun_shot;
};
}//namespace client
