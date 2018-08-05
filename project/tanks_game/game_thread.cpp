#include "game_thread.h"

namespace game {
Game_Thread_Sender::Game_Thread_Sender(QTcpSocket*socket, const ServerBuffer &respond, QObject *parent)
  : QThread(parent), socketDescriptor(socketDescriptor), respond(respond), current_socket(socket){

}
//
//bool Game_Thread::sendBuffer(QByteArray block) {
//  if (socket->state() == QAbstractSocket::ConnectedState) {
//    socket->write(IntToArray(block.size())); //write size of data
//    socket->write(block); //write the data itself
//    return socket->waitForBytesWritten();
//  } else
//    return false;
//}
void Game_Thread_Sender::run() {
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_10);
  out << respond;
  current_socket->write(IntToArray(block.size())); //write size of data
  current_socket->write(block); //write the data itself
  current_socket->waitForBytesWritten();
  //tcpSocket.disconnectFromHost();
  //tcpSocket.waitForDisconnected();
}

} //namesapce game

