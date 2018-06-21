#ifndef TANK_H
#define TANK_H
#include "body.h"
#include "turret.h"
#include "track.h"
#include "action.h"
#include "gamepadmngr.h"


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
};

} //namespace Tank

#endif // TANK_H
