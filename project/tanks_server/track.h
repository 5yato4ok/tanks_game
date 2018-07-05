#ifndef TRACK_H
#define TRACK_H
#include "action.h"
#include "stdint.h"
#include "arduino_sender.h"
#include "ui_tanks_server.h"
//TODO: describe limit
namespace tank {
  
class Track_mngr:public QObject {
  Q_OBJECT
 public:
  Track_mngr(Ui_MainWindow* gui, QHostAddress steel_ip = QHostAddress::Any,
    quint16 steel_port = 34005);
  tank_status ManageAction(TankAction& action);
 private:
  Ui_MainWindow* gui;
  int32_t change_velocity();
  int32_t change_direction();
  void get_direction(double value_x, double value_y);
  int32_t get_velocity(double value_x,double value_y);
  int32_t velocity; //in percetage
  direction up_down;
  direction left_right;
};
}//namespace tank

#endif // TRACK_H
