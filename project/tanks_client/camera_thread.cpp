#include "camera_thread.h"

namespace client {
Camera_Thread::Camera_Thread(Ui::Tanks_ClientClass* ui_, QObject *parent):
  ui(ui_) ,QThread(parent){
  stop = true;
}

bool Camera_Thread::LoadVideo(std::string camera_url) {
  capture = cv::VideoCapture(camera_url);
  ui->output->appendPlainText("Input stream: " + QString::fromStdString(camera_url));
  if (capture.isOpened()) {
    frameRate = (int)capture.get(CV_CAP_PROP_FPS);
    return true;
  }   
  ui->output->appendPlainText("OpenCV Failed::: can't open input stream:" + QString::fromStdString(camera_url));
  return false;
}

void Camera_Thread::Play() {
  if (!isRunning()) {
    if (isStopped()) {
      stop = false;
    }
    start(LowPriority);
  }
}

void Camera_Thread::run() {
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

Camera_Thread::~Camera_Thread() {
  mutex.lock();
  stop = true;
  capture.release();
  condition.wakeOne();
  mutex.unlock();
  wait();
}
void Camera_Thread::Stop() {
  stop = true;
}
void Camera_Thread::msleep(int ms) {
  //struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
  //nanosleep(&ts, NULL);
  sleep(ms / 1000);
}
bool Camera_Thread::isStopped() const {
  return this->stop;
}

} //namespace client
