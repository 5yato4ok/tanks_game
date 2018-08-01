#include "camera.h"

namespace client {
Camera::Camera(Ui::Tanks_ClientClass* ui_, QObject *parent): ui(ui_),
 camera(Camera_Thread(ui_,parent)){
  QObject::connect(&camera, SIGNAL(processedImage(QImage)),
    this, SLOT(updatePlayerUI(QImage)));
}

void Camera::updatePlayerUI(QImage img) {
  if (!img.isNull()) {
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),
      Qt::KeepAspectRatio, Qt::FastTransformation));
  }
}

void Camera::StartVideo() {
  if (camera.isStopped()) {
    camera.Play();
  } 
}

void Camera::StopVideo() {
  if (!camera.isStopped()) {
    camera.Stop();
  }
}

bool Camera::LoadVideo(std::string camera_url) {
  camera.Exit();
  return  camera.LoadVideo(camera_url);
}

} //namespace client
