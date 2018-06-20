#ifndef GAMEPADMNGR_H
#define GAMEPADMNGR_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGamepad/QGamepad>
#include <QDebug>
#include "action.h"

//TODO: make action setting window
// TODO: make opportunity to more than one button

class GamePadMngr : public QObject {
  Q_OBJECT
 public:
  explicit GamePadMngr(QObject *parent = nullptr);
  void Listen_Input();
  bool Is_connected();
  ~GamePadMngr();
  //signals
  void connectedChangedEvent(bool value);
  void sendAction(Action buffer);
 private:
  QGamepad* m_gamepad;
  void axisLeftX_packet(double value);
  void axisLeftY_packet(double value);
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

};

#endif // GAMEPADMNGR_H
