#pragma once
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ui_tanks_client.h"
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>

//#include <opencv2/avcodec.h>
//#include <opencv2/avformat.h>
//#include <opencv2/swscale.h>
namespace client {

class Camera_Init_Thread : public QThread {
  Q_OBJECT
public:
  Camera_Init_Thread(cv::VideoCapture& capture, Ui::Tanks_ClientClass* ui, 
    QObject *parent = nullptr);
  Camera_Init_Thread::Camera_Init_Thread(Camera_Init_Thread && copy);
  Camera_Init_Thread(const Camera_Init_Thread&) = delete;
  Camera_Init_Thread& operator=(const Camera_Init_Thread&) = delete;
  void OpenVideo(std::string camera_url);
  ~Camera_Init_Thread();
 signals:
  void camera_initialized(bool);
 protected:
  void run() override;
 private:
  Ui::Tanks_ClientClass* ui;
  std::string camera_url;
  QMutex mutex;
  QWaitCondition condition;
  cv::VideoCapture& capture;
};

}//namespace client