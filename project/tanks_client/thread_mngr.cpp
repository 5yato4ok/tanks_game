#include "thread_mngr.h"

GamePadThread::GamePadThread():thread(new QThread()) {
  connect(thread, &QThread::started, this, &GamePadThread::ThreadLoop);
  axis_condition[input_state.button].current.x = 0;
  axis_condition[input_state.button].current.y = 0;
}

GamePadThread::~GamePadThread() {
  thread->exit();
}
void GamePadThread::Start() {
  thread->start();
}

void GamePadThread::Exit() {
  if (thread->isRunning()) {
    thread->exit();
  }
}

void GamePadThread::SetAxis_x(double x,gp_helper::gp_buttons button) {
  mutex.lock();
  input_state.button = button;
  input_state.value_x = x;
  input_state.is_pressed = true;
  axis_condition[button].current.x = x;
  mutex.unlock();
}
void GamePadThread::SetAxis_y(double y,gp_helper::gp_buttons button) {
  mutex.lock();
  input_state.button = button;
  input_state.value_y = y;
  input_state.is_pressed = true;
  axis_condition[button].current.y = y;
  mutex.unlock();
}

void GamePadThread::SetRawAction(Raw_Action buffer) {
  //if (thread->isRunning()) {
  //  thread->exit();
  //}
  mutex.lock();
  switch (buffer.button) {
  case gp_helper::gp_buttons::AXIS_LEFT:
  case gp_helper::gp_buttons::AXIS_RIGHT:
    //axis_condition[buffer.button].current.x = buffer.value_x;
    //axis_condition[buffer.button].current.y = buffer.value_y;
    break;
  default:
    input_state = buffer;
    condition_state[input_state.button] = buffer.is_pressed;
    break;
  }
  mutex.unlock();
}

void GamePadThread::ThreadLoop() {
  axis_condition[input_state.button].previos = axis_condition[input_state.button].current;
  switch (input_state.button) {
  case gp_helper::gp_buttons::AXIS_LEFT:
  case gp_helper::gp_buttons::AXIS_RIGHT: {
    bool is_stop = true;
    while (axis_condition[input_state.button].current
      == axis_condition[input_state.button].previos  &&is_stop) {
      is_stop = false;
      QEventLoop loop;
      QTimer::singleShot(250, &loop, SLOT(quit()));
      loop.exec();
      emit is_same(input_state);
    }
    qDebug() << "Out of while loop.Thread";
    break;
  }
   default:
     while (condition_state[input_state.button]) {
       QEventLoop loop;
       QTimer::singleShot(250, &loop, SLOT(quit()));
       loop.exec();
       emit is_same(input_state);
     }
     break;
  }
}
