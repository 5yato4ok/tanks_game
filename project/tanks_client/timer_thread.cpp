#include "timer_thread.h"

namespace client {
TimerThread::TimerThread(int ms_):ms(ms_) {
  connect(&thread, &QThread::started, this, &TimerThread::thread_loop);
}

TimerThread::~TimerThread() {
  thread.exit();
}
void TimerThread::Start() {
  thread.start();
}

void TimerThread::Exit() {
  if (thread.isRunning()) {
    thread.exit();
  }
}

void TimerThread::thread_loop() {
  QEventLoop loop;
  QTimer::singleShot(ms, &loop, SLOT(quit()));
  loop.exec();
  emit exit_timer();
}

}