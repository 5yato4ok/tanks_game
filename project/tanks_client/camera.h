#pragma once
#include <QObject>
#include "camera_thread.h"
namespace client {
class Camera: public QObject {
  Q_OBJECT
 public:
   Camera(Ui::Tanks_ClientClass* ui, QObject *parent = nullptr);
   bool LoadVideo(std::string camera_url);
   void StartVideo();
   void StopVideo();
 private slots:
   //Display video frame in player UI
   void updatePlayerUI(QImage img);
 private:
  Ui::Tanks_ClientClass* ui;
  Camera_Thread camera;

};
} //namespace client
