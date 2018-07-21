#include "track_thread.h"

namespace tank {

TrackThread::TrackThread() :thread(new QThread()) {
  connect(thread, &QThread::started, this, &TrackThread::Thread_Send_Sequence);
}

TrackThread::~TrackThread() {
  thread->exit();
}


void TrackThread::Start() {
  thread->start();
}

void TrackThread::Exit() {
  if (thread->isRunning()) {
    thread->exit();
    Tank_Tracks null_packet;
    null_packet.left_track.velocity = 0;
    null_packet.right_track.velocity = 0;
    null_packet.right_track.is_right = true;
    emit send_action(current);
  }
}

void TrackThread::SetPacket(Tank_Tracks& current_, Tank_Tracks& required_) {
  mutex.lock();
  current = current_;
  required = required_;
  mutex.unlock();
}

int8_t TrackThread::calculate_delta() {
  int8_t left_delta = abs(current.left_track.velocity - required.left_track.velocity);
  int8_t right_delta = abs(current.right_track.velocity - required.right_track.velocity);
  return left_delta > right_delta ? left_delta : right_delta;
}

void TrackThread::Thread_Send_Sequence() {
  current.left_track.up_down = required.left_track.up_down;
  current.right_track.up_down = required.right_track.up_down;
  current.right_track.is_right = true;
  if (!required.left_track.velocity && !required.right_track.velocity) {
    current = required;
    emit send_action(current);
    return;
  }
  int8_t delta = calculate_delta();
  for (int i = 0; i < delta; i+=5) {
    //QEventLoop loop;
    //QTimer::singleShot(10, &loop, SLOT(quit()));
    //loop.exec();
    if (required.left_track < current.left_track) {
      current.left_track.velocity -= i;
    } else if (required.left_track == current.left_track) {
      current.left_track = required.left_track;
    } else {
      current.left_track.velocity += i;
    }
    if (required.right_track < current.right_track) {
      current.right_track.velocity -= i;
    } else if (required.left_track == current.left_track) {
      current.right_track = required.right_track;
    } else {
      current.right_track.velocity += i;
    }
    current.right_track.is_right = true;
    emit send_action(current);
  }
}
}