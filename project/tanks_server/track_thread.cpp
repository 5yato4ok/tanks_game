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
  if (!required.left_track.velocity && !required.right_track.velocity) {
    current = required;
    emit send_action(current);
    return;
  }
  int8_t delta = calculate_delta();
  for (int i = 0; i < delta; i++) {
    if (required.left_track < current.left_track) {
      current.left_track.velocity -= 1;
    } else if (required.left_track == current.left_track) {
      current.left_track = current.left_track;
    } else {
      current.left_track.velocity += 1;
    }
    if (required.right_track < current.right_track) {
      current.right_track.velocity -= 1;
    } else if (required.left_track == current.left_track) {
      current.right_track = current.right_track;
    } else {
      current.right_track.velocity += 1;
    }
    emit send_action(current);
  }
}
}