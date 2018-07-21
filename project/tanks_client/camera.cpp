#include "camera.h"

namespace client {
Camera::Camera(Ui::Tanks_ClientClass* ui_, QObject *parent):
  ui(ui_) ,QThread(parent){
  stop = true;
}

bool Camera::LoadVideo(std::string camera_url) {
  // Открываем поток с камеры средствами OpenCV
  //capture = cv::VideoCapture(camera_url);
  ui->output->appendPlainText("Input stream: " + QString::fromStdString(camera_url));
  //if (capture.isOpened()) {
  //  frameRate = (int)capture.get(CV_CAP_PROP_FPS);
  //  return true;
  //}   
  ui->output->appendPlainText("OpenCV Failed::: can't open input stream:" + QString::fromStdString(camera_url));
  return false;
}

void Camera::Play() {
  if (!isRunning()) {
    if (isStopped()) {
      stop = false;
    }
    start(LowPriority);
  }
}

Camera::~Camera() {
  if (ui) {
    delete ui;
  }
}

} //namespace client
