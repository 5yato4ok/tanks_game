#pragma once

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
#include "server_buffer.h"
namespace game {
class Game_Thread : public QThread {
  Q_OBJECT
public:
  Game_Thread(int socketDescriptor, const ServerBuffer &respond, QObject *parent);
  void run() override;

signals:
  void error(QTcpSocket::SocketError socketError);
private:
  //bool sendBuffer(QByteArray block);
  //player_map_with_current_rules
  int socketDescriptor;
  ServerBuffer respond;
};
} // game
