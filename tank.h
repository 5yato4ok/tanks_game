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
  explicit TankMngr(GamePadMngr* gamepad, QObject *parent = nullptr);
  bool Is_initialized() { return is_intialized_; }
  void Init_signals();
 signals:
  void SendActionToMngr(const Action&);
 public slots:
  void ReceiveData(Action buffer);
 private:
  GamePadMngr* gamepad;
  Turret_mngr turet;
  Track_mngr track;
  Body_mngr body_mngr;
  bool is_intialized_;
};

} //namespace Tank

#endif // TANK_H
