#ifndef VISION_H
#define VISION_H
#include "action.h"
#include "ui_tanks_server.h"
#include "server_buffer.h"
namespace tank {

class Vision_mngr {
 public:
   explicit Vision_mngr(Ui_MainWindow* gui);
 private:
  Ui_MainWindow* gui;
  void zoom();
  //here some camera OpenCV class
};
}
#endif // VISION_H
