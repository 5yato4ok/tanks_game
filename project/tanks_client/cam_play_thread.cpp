#include "cam_play_thread.h"

namespace client {
Camera_Play_Thread::Camera_Play_Thread(Ui::Tanks_ClientClass* ui_, cv::VideoCapture& capture_, QObject *parent) :
ui(ui_), QThread(parent), capture(capture_){
  stop = true;
}

Camera_Play_Thread::Camera_Play_Thread(Camera_Play_Thread && copy): 
  capture(copy.capture),ui(copy.ui) {

}

bool Camera_Play_Thread::GetFramInfo() {
  if (capture.isOpened()) {
    frameRate = (int)capture.get(CV_CAP_PROP_FPS);
    return true;
  }
  ui->output->appendPlainText("OpenCV Failed:: Capture isn't open");
  return false;
}

void Camera_Play_Thread::Play() {
  if (!isRunning()) {
    if (isStopped()) {
      stop = false;
    }
    start(HighPriority);
  }
}

void Camera_Play_Thread::run() {
  if (!capture.isOpened()) {
    return;
  }
  
  int delay = (1000 / frameRate);
  while (!stop) {
    if (!capture.read(frame)) {
      stop = true;
    }
    if (frame.channels() == 3) {
      cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
      img = QImage((const unsigned char*)(RGBframe.data),
        RGBframe.cols, RGBframe.rows, QImage::Format_RGB888);
    } else {
      img = QImage((const unsigned char*)(frame.data),
        frame.cols, frame.rows, QImage::Format_Indexed8);
    }
    emit processedImage(img);
    this->msleep(delay);
  }
}

void Camera_Play_Thread::Stop() {
  stop = true;
}
void Camera_Play_Thread::msleep(int ms) {
  //struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
  //nanosleep(&ts, NULL);
  sleep(ms / 1000);
}
bool Camera_Play_Thread::isStopped() const {
  return this->stop;
}
Camera_Play_Thread::~Camera_Play_Thread() {
  stop = true;
}
} //namespace client