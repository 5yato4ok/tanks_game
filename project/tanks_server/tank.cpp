#include "tank.h"
namespace tank {
TankMngr::TankMngr(Ui_MainWindow* gui_) : 
 is_intialized_(false),Player_server(gui_),ard_mngr(gui_),
 tower(gui_,ard_mngr),track(gui_,ard_mngr) {
  connect(this, &Player_server::server_started, this, &TankMngr::init_receive_port);
  connect(this, SIGNAL(tankDataReceived(TankAction)), SLOT(ReceiveClientData(TankAction)));
  connect(&ard_mngr, &ArduinoSender::tankDataReceived, this, &TankMngr::ReceveArduinoData);
}

void TankMngr::ReceveArduinoData(std::string buffer_) {
  if (buffer_.find("BH") != std::string::npos) {
    ServerBuffer buffer;
    buffer.type = msg_type::GAME_BUFFER;
    buffer.size = buffer_.size();
    memset(buffer.tankAction, 0, 1024);
    memcpy(buffer.tankAction, buffer_.data(), buffer_.size());
    //some initialization based on buffer
    Player_server::ManageArduinoInfo(buffer);
  }
}

void TankMngr::ReceiveClientData(TankAction buffer) {
  gui->tank_out->appendPlainText("TankMngr Received Data. Switching the type");
 switch (buffer.type) {
  case action_type::MOVE_GUN_UP:
  case action_type::MOVE_GUN_DOWN:
  case action_type::MOVE_TOWER_LEFT:
  case action_type::MOVE_TOWER_RIGHT:
    tower.ManageAction(buffer);
    break;
  case action_type::MOVE_TRACK:
    track.ManageAction(buffer);
    break;
  }
}

void TankMngr::init_receive_port(int32_t tank_id) {
  switch (tank_id) {
  case g_server_port_0:
    is_intialized_ = ard_mngr.Init(ip_tank_0, port_in,port_out);
    break;
  case g_server_port_1:
    is_intialized_ = ard_mngr.Init(ip_tank_1, port_in, port_out);
    break;
  case g_server_port_2:
    is_intialized_ = ard_mngr.Init(ip_tank_2, port_in, port_out);
    break;
  default:
    is_intialized_ = false;
    return;
  }
  std::string tmp = "V";
  ard_mngr.SendAction(tmp);
  if (!is_intialized_) {
    gui->player_out->appendPlainText("Tank::Connection failure");
  }

  //ReceveArduinoData("BH_1");
}

} //namespace Tank
