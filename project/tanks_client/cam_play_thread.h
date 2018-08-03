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

class Camera_Play_Thread : public QThread {
  Q_OBJECT
public:
  Camera_Play_Thread(Ui::Tanks_ClientClass* ui, cv::VideoCapture& capture,QObject *parent = nullptr);
  ~Camera_Play_Thread();
  Camera_Play_Thread(Camera_Play_Thread &&);
  Camera_Play_Thread(const Camera_Play_Thread&) = delete;
  Camera_Play_Thread& operator=(const Camera_Play_Thread&) = delete;
  bool GetFramInfo();
  void Play();
  void Stop();
  bool isStopped() const;
signals:
  //Signal to output frame to be displayed
  void processedImage(const QImage &image);
protected:
  void run() override;
  void msleep(int ms);
private:
  Ui::Tanks_ClientClass* ui;
  bool stop;
  cv::Mat frame;
  int frameRate;
  cv::VideoCapture& capture;
  cv::Mat RGBframe;
  QImage img;
};

}//namespace client