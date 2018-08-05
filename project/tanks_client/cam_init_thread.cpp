#include "cam_init_thread.h"

namespace client {

Camera_Init_Thread::Camera_Init_Thread(cv::VideoCapture& capture_, Ui::Tanks_ClientClass* ui_,
  QObject *parent): capture(capture_),ui(ui_) {

}

Camera_Init_Thread::Camera_Init_Thread(Camera_Init_Thread && copy) :
  capture(copy.capture), ui(copy.ui) {
}

void Camera_Init_Thread::OpenVideo(std::string camera_url_) {
  camera_url = camera_url_;
  ui->connect_server->setEnabled(false);
  ui->output->appendPlainText(QTime::currentTime().toString()+"Starting to load video. It may take some time:");
  ui->output->appendPlainText("Input stream: " + QString::fromStdString(camera_url));
  if (!isRunning()) {
    start(HighPriority);
  }
}

void Camera_Init_Thread::run() {
  capture.open(camera_url,cv::CAP_FFMPEG);// cv::CAP_GSTREAMER);
  emit camera_initialized(capture.isOpened());
}

Camera_Init_Thread::~Camera_Init_Thread() {
  mutex.lock();
  capture.release();
  condition.wakeOne();
  mutex.unlock();
  wait();
}
} //namespace client
