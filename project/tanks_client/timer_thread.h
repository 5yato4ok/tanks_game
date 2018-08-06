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

namespace client {
  class TimerThread : public QObject {
    Q_OBJECT
  public:
    TimerThread(int ms);
    ~TimerThread();
    void Start();
    void Exit();
  signals:
    void exit_timer();
  private:
    int ms;
    void thread_loop();
    QThread thread;
  };

} //namesapce client

