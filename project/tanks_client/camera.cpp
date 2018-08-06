#include "camera.h"

namespace client {
Camera::Camera(Ui::Tanks_ClientClass* ui_, QObject *parent) :ui(ui_),
  init_thread(Camera_Init_Thread(capture,ui_,parent)),
  play_thread(Camera_Play_Thread(ui_, capture,  parent)) {
  QObject::connect(&play_thread, SIGNAL(processedImage(QImage)),
    this, SLOT(updatePlayerUI(QImage)));
  connect(&init_thread, &Camera_Init_Thread::camera_initialized, this, 
    &Camera::loading_complete);
}

void Camera::updatePlayerUI(QImage img) {
  if (!img.isNull()) {
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),
      Qt::KeepAspectRatio, Qt::FastTransformation));
  }
}

void Camera::StartVideo() {
  if (play_thread.GetFramInfo()&&play_thread.isStopped()) {
    play_thread.Play();
  }
}

void Camera::StopVideo() {
  if (!play_thread.isStopped()) {
    play_thread.Stop();
  }
}

void Camera::loading_complete(bool is_loaded) {
  //ui->connect_server->setEnabled(true);
  if (is_loaded) {
    ui->output->appendPlainText("Video is succesfuly loaded.");
    emit video_loaded();
  } else {
    ui->output->appendPlainText("Video loading error.");
  }
}

void Camera::LoadVideo(std::string camera_url) {
  init_thread.OpenVideo(camera_url);
}

Camera::~Camera() {
  if (init_thread.isRunning()) {
    init_thread.exit();
  }
  if (play_thread.isRunning()) {
    play_thread.exit();
  }
}

} //namespace client
