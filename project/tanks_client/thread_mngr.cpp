#include "thread_mngr.h"

GamePadThread::GamePadThread():thread(new QThread()) {
  connect(thread, &QThread::started, this, &GamePadThread::ThreadLoop);
}

void GamePadThread::Start() {
  thread->start();
}

void GamePadThread::Exit() {
  thread->exit();
}
void GamePadThread::SetCondition(gp_helper::gp_buttons button, double condition_) {
  if (thread->isRunning()) {
    thread->exit();
  }
  mutex.lock();
  condition_state[button] = condition_;
  mutex.unlock();
}

void GamePadThread::SetRawAction(Raw_Action buffer) {
  mutex.lock();
  input_state = buffer;
  mutex.unlock();
}

void GamePadThread::ThreadLoop() {
  //mutex.lock();
  while (condition_state[input_state.button]) {
    //mutex.unlock();
    QEventLoop loop;
    QTimer::singleShot(500, &loop, SLOT(quit()));
    loop.exec();
    emit is_same(input_state);
  }
  //mutex.unlock();
}