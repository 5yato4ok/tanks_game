#include "game_server.h"

namespace game{
Game_Server::Game_Server(QTcpServer* parent):QTcpServer(parent), socket_client(new QTcpSocket()){

}

void Game_Server::manage_client_buffer(ServerBuffer& buffer) {

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
        manage_client_buffer(buffer);
      }
    }
  }
}

void Game_Server::incomingConnection(qintptr socketDescriptor) {
  connect(socket_client, &QTcpSocket::readyRead, this, &Game_Server::readyRead);
  ServerBuffer tmp;
  QByteArray *buffer = new QByteArray();
  qint32 *s = new qint32(0);
  buffers.insert(socket_client, buffer);
  sizes.insert(socket_client, s);
  Game_Thread *thread = new Game_Thread(socketDescriptor, tmp , this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();
}
}//namespace game

