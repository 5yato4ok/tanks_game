#ifndef GAMEPADMNGR_H
#define GAMEPADMNGR_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGamepad/QGamepad>
#include <QDebug>
#include "action.h"
#include "default_gp_settings.h"

// TODO: make opportunity to use more than one button
// TODO: test more than one gamepad connection
// TODO: add disconnect function

struct Raw_Action {
  gp_helper::gp_buttons button;
  double value_x;
  double value_y;
};


namespace gp_helper {


class GamePadMngr : public QObject {
  Q_OBJECT
public:
  explicit GamePadMngr(QObject *parent = nullptr);
  void Listen_Input();
  bool Is_connected();
  ~GamePadMngr();
  void connectedChangedEvent(bool value);
signals:
  void sendAction(Raw_Action buffer);
private:
  QGamepad* m_gamepad;
  void axisLeftX_packet(double value);
  void axisRightX_packet(double value);
  void axisLeftY_packet(double value);
  void axisRightY_packet(double value);
  void buttonA_packet(bool pressed);
  void buttonB_packet(bool pressed);
  void buttonX_packet(bool pressed);
  void buttonY_packet(bool pressed);
  void buttonL1_packet(bool pressed);
  void buttonR1_packet(bool pressed);
  void buttonL2_packet(double value);
  void buttonR2_packet(double value);
  void buttonSelect_packet(bool pressed);
  void buttonStart_packet(bool pressed);
  void buttonGuide_packet(bool pressed);
  void buttonUP_packet(bool value);
  void buttonDOWN_packet(bool pressed);
  void buttonLEFT_packet(bool pressed);
  void buttonRIGHT_packet(bool pressed);

};
}//namespace gp_helper
#endif // GAMEPADMNGR_H
