#pragma once
#include <QThread>
#include <QMutex>
#include <QByteArray>
#include <QEventLoop>
#include "default_gp_settings.h"
#include <map>
#include <Qtimer>

using Button_state = std::map<gp_helper::gp_buttons, double>;

class GamePadThread: public QObject {
  Q_OBJECT
 public:
   GamePadThread();
   void SetCondition(gp_helper::gp_buttons button, double condition);
   void SetRawAction(Raw_Action buffer);
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
};