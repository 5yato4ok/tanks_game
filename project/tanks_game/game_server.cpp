#include "game_server.h"

namespace game{
Game_Server::Game_Server(QTcpServer* parent):QTcpServer(parent) {
}
void Game_Server::incomingConnection(qintptr socketDescriptor) {
  ServerBuffer tmp;
  Game_Thread *thread = new Game_Thread(socketDescriptor, tmp , this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();
}
}//namespace game

