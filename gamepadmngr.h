#ifndef GAMEPADMNGR_H
#define GAMEPADMNGR_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGamepad/QGamepad>
#include <QDebug>

class GamePadMngr : public QObject {
  Q_OBJECT
 public:
  explicit GamePadMngr(QObject *parent = nullptr);
  void Listen_Input();
  bool Is_connected();
  ~GamePadMngr();
 private:
 void connectedChangedEvent(bool value);
  QGamepad* m_gamepad;
  //gamepad;
signals:

public slots:
};

#endif // GAMEPADMNGR_H
