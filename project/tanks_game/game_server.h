#pragma once
#include "rules.h"
#include "game_type.h"
#include "game_thread.h"
#include <vector>
#include <QObject>
#include <QtNetwork>
#include "server_buffer.h"
//So we will hearing some port.Read it.
//in packet should be sender
//Send action on buffer to sender
//should do it in thread
//Packets:
//GetRules. return packet with lifes
//operate action
namespace game {
class Game_Server: public QTcpServer {
  Q_OBJECT
 public:
  explicit Game_Server(QTcpServer* parent = nullptr);
 protected:
  void incomingConnection(qintptr socketDescriptor) override;
 private:
  std::map<QTcpSocket*, int> players_lifes;
  QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
  QHash<QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely
  Rules game_rules;
  void readyRead();
};
}//namespace game

