#ifndef TANK_H
#define TANK_H
#include "body.h"
#include "turret.h"
#include "track.h"
#include "action.h"
#include "gamepadmngr.h"

// TODO: make action setting window from qt example

namespace tank {
class TankMngr:QObject {
  Q_OBJECT
 public:
  explicit TankMngr(QObject *parent = nullptr);
  bool Is_initialized() { return is_intialized_; }
  void Connect_signals();
  void Disconnect_signals();
 public slots:
  void ReceiveData(gp_helper::Raw_Action buffer);
 private:
  void init_supported_buttons();
  bool is_tank_action(gp_helper::Raw_Action& buffer);

  bool is_turret_action(gp_helper::Raw_Action& buffer);
  TankAction get_turret_action(gp_helper::Raw_Action& buffer);


  bool is_body_action(gp_helper::Raw_Action& buffer);
  TankAction get_body_action(gp_helper::Raw_Action& buffer);


  bool is_track_action(gp_helper::Raw_Action& buffer);
  TankAction get_track_action(gp_helper::Raw_Action& buffer);

  gp_helper::GamePadMngr gamepad;
  Turret_mngr turret;
  Track_mngr track;
  Body_mngr body_mngr;
  bool is_intialized_;
  std::vector<gp_helper::gp_buttons> supported_buttons;
};

} //namespace Tank

#endif // TANK_H
