#pragma once
#include <QThread>
#include <QMutex>
#include <qdebug>
#include <QByteArray>
#include <QEventLoop>
#include "default_gp_settings.h"
#include <map>
#include <Qtimer>
#include <qwaitcondition.h>

using Button_state = std::map<gp_helper::gp_buttons, double>;

class Axis_values {
 public:
  Axis_values() {};
  double x;
  double y;
  bool operator ==(const Axis_values& rhs) const {
    return (x == rhs.x) && (y == rhs.y);
  }
};

class Axis_state {
 public:
  Axis_state() {};
  Axis_values previos;
  Axis_values current;
  bool operator <(const Axis_state& rhs) const {
    return previos.x < current.x;
  }
};

using Axis_condition = std::map<gp_helper::gp_buttons, Axis_state>;
class GamePadThread: public QObject {
  Q_OBJECT
 public:
   GamePadThread();
   ~GamePadThread();
   void SetRawAction(Raw_Action buffer);
   void SetAxis_x(double x,gp_helper::gp_buttons button = gp_helper::gp_buttons::AXIS_RIGHT);
   void SetAxis_y(double y, gp_helper::gp_buttons button = gp_helper::gp_buttons::AXIS_RIGHT);
   void ThreadLoop();
   void Start();
   void Exit();

 signals:
  void is_same(Raw_Action buffer);
 private:
   QThread* thread;
   Raw_Action input_state;
   QMutex mutex;
   Button_state condition_state;
   Axis_condition axis_condition;
};