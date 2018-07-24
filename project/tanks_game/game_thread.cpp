#include "game_thread.h"

namespace game {
QByteArray IntToArray(qint32 source) {
  //Avoid use of cast, this is the Qt way to serialize objects
  QByteArray temp;
  QDataStream data(&temp, QIODevice::ReadWrite);
  data << source;
  return temp;
};

qint32 ArrayToInt(QByteArray source) {
  qint32 temp;
  QDataStream data(&source, QIODevice::ReadWrite);
  data >> temp;
  return temp;
}

  Game_Thread::Game_Thread(int socketDescriptor, const ServerBuffer &respond, QObject *parent)
  : QThread(parent), socketDescriptor(socketDescriptor), respond(respond) {}
//
//bool Game_Thread::sendBuffer(QByteArray block) {
//  if (socket->state() == QAbstractSocket::ConnectedState) {
//    socket->write(IntToArray(block.size())); //write size of data
//    socket->write(block); //write the data itself
//    return socket->waitForBytesWritten();
//  } else
//    return false;
//}
void Game_Thread::run() {
  QTcpSocket tcpSocket;
  if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
    emit error(tcpSocket.error());
    return;
  }
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_10);
  out << respond;
  tcpSocket.write(IntToArray(block.size())); //write size of data
  tcpSocket.write(block); //write the data itself
  tcpSocket.waitForBytesWritten();
  tcpSocket.disconnectFromHost();
  tcpSocket.waitForDisconnected();
}

} //namesapce game

