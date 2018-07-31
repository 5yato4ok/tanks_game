#ifndef TANK_H
#define TANK_H
#include "body.h"
#include "tower.h"
#include "tracks.h"
#include "action.h"
#include "player_server.h"

// TODO: make action setting window from qt example

namespace tank {
class TankMngr: public game::Player_server {
  Q_OBJECT
 public:
  explicit TankMngr(Ui_MainWindow* gui);
  bool Is_initialized() { return is_intialized_; }
 signals:
  void GetArduinoInfo(); //TankInfo
 public slots:
  void ReceiveClientData(TankAction buffer);
  void ReceveArduinoData(std::string buffer); //TODO: change to some buffer
 private:
  quint16 steel_port;
  QHostAddress steel_ip;
  QString camera_url;
  int32_t tank_id;
  void init_receive_port(int32_t tank_id);
  ArduinoSender ard_mngr;
  Tower_mngr tower;
  Track_mngr track;
  Body_mngr body_mngr;
  bool is_intialized_;
};

} //namespace Tank

#endif // TANK_H
