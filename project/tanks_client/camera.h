#pragma once
#include <QObject>
#include "cam_play_thread.h"
#include "cam_init_thread.h"
namespace client {
class Camera : public QObject {
  Q_OBJECT
 public:
  Camera(Ui::Tanks_ClientClass* ui, QObject *parent = nullptr);
  ~Camera();
  void LoadVideo(std::string camera_url);
  void StartVideo();
  void StopVideo();
 signals:
  void video_loaded();
 private slots:
  //Display video frame in player UI
  void updatePlayerUI(QImage img);
  void loading_complete(bool);
 private:
  bool is_loaded = false;
  Ui::Tanks_ClientClass* ui;
  cv::VideoCapture capture;
  Camera_Init_Thread init_thread;
  Camera_Play_Thread play_thread;

  };
} //namespace client