#ifndef TANK_H
#define TANK_H
#include "body.h"
#include "tower.h"
#include "track.h"
#include "action.h"

// TODO: make action setting window from qt example

namespace tank {
class TankMngr:QObject {
  Q_OBJECT
 public:
  explicit TankMngr(QObject *parent = nullptr);
  bool Is_initialized() { return is_intialized_; }
 public slots:
  void ReceiveData(TankAction buffer);
 private:
  void init_receive_port();
  Tower_mngr tower;
  Track_mngr track;
  Body_mngr body_mngr;
  bool is_intialized_;
};

} //namespace Tank

#endif // TANK_H
