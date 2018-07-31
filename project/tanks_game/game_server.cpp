#include "game_server.h"

namespace game{
Game_Server::Game_Server(QTcpServer* parent):QTcpServer(parent){
  Rules buf = { 0 };
  buf.number_life = 10;
}

void Game_Server::readyRead() {
  QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
  QByteArray *buffer = buffers.value(socket);
  qint32 *s = sizes.value(socket);
  qint32 size = *s;
  //gui->player_out->appendPlainText("Started readyRead()");
  //gui->centralWidget->update();
  //gui->centralWidget->update();
  while (socket->bytesAvailable() > 0) {
    buffer->append(socket->readAll());
    //While can process data, process it
    //gui->player_out->appendPlainText("Reading data");
    //gui->centralWidget->update();
    while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) {
      //if size of data has received completely, then store it on our global variable
      if (size == 0 && buffer->size() >= 4) {
        size = ArrayToInt(buffer->mid(0, 4));
        *s = size;
        buffer->remove(0, 4);
      }
      //gui->player_out->appendPlainText("Storing received data");
      //gui->centralWidget->update();
      if (size > 0 && buffer->size() >= size) {
        QByteArray data = buffer->mid(0, size);
        buffer->remove(0, size);
        size = 0;
        *s = size;
        ServerBuffer buffer;
        memcpy(&buffer, data.data(), data.size());
        //manage_client_buffer(buffer);
      }
    }
  }
}

void Game_Server::incomingConnection(qintptr socketDescriptor) {
  ServerBuffer tmp;
  memset(&tmp, 0, sizeof(ServerBuffer));
  tmp.type = msg_type::GAME_BUFFER;
  tmp.size = sizeof(Rules);
  memcpy(tmp.tankAction, &game_rules, sizeof(Rules));
  //init_new_player
  QTcpSocket* new_player = new QTcpSocket();
  new_player->setSocketDescriptor(socketDescriptor);
  players_lifes[new_player] = 10;
  QByteArray *buffer = new QByteArray();
  qint32 *s = new qint32(0);
  buffers.insert(new_player, buffer);
  sizes.insert(new_player, s);
  //some map with sockets and rules. for now it will be only number of life
  //socket_client = tcpServer->nextPendingConnection();
  //connect this socket with readRead in wich called
  //So here not send on connection anything
  connect(new_player, &QTcpSocket::readyRead, this, &Game_Server::readyRead);
  //connect(socket_client, &QTcpSocket::disconnected, this, &Player_server::disconnected);
  Game_Thread_Sender *thread = new Game_Thread_Sender(socketDescriptor, tmp , this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();
}
}//namespace game

