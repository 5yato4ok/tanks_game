#pragma once
#include <QThread>
#include <QMutex>
#include <qdebug>
#include <QByteArray>
#include <QEventLoop>
#include <Qtimer>
#include <qwaitcondition.h>
#include "track.h"

namespace tank {

class TrackThread : public QObject {
  Q_OBJECT
public:
  TrackThread();
  ~TrackThread();
  void SetPacket(Tank_Tracks& current, Tank_Tracks& required);
  void Thread_Send_Sequence();
  void Start();
  void Exit();
signals:
  void send_action(Tank_Tracks tracks_descr);
private:
  int8_t calculate_delta();
  QThread* thread;
  Tank_Tracks current;
  Tank_Tracks required;
  QMutex mutex;
};

} //namespace tank
