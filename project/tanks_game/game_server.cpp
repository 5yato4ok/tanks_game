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
        manage_client_buffer(socket,buffer);
      }
    }
  }
}


std::string Game_Server::get_hitted_by(ServerBuffer& buffer) {
  std::string hitted_by(buffer.tankAction, buffer.size);
  auto start_position_to_erase = hitted_by.find("BH");
  std::string player_number = "Player"+hitted_by.erase(start_position_to_erase, 2);
  return player_number;

}

void Game_Server::start_sending_thread(qintptr socketDescriptor, ServerBuffer buffer) {
  Game_Thread_Sender *thread = new Game_Thread_Sender(socketDescriptor, buffer, this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();
}
ServerBuffer Game_Server::change_cpc(ServerBuffer& buffer_, QTcpSocket *socket) {
  //make here checking on is this socet in hash
  ServerBuffer responce;
  memset(&responce, 0, sizeof(ServerBuffer));
  responce.type = msg_type::GAME_RESPONCE;
  
  if (players_lifes[socket].current_life > 0) {
    players_lifes[socket].current_life -= 1;
    auto hit_s = get_hitted_by(buffer_);
    auto current_descr = players_lifes[socket];
    memcpy(current_descr.hitted_by, hit_s.c_str(), hit_s.size());
    current_descr.size = hit_s.size();
    memcpy(responce.tankAction, &current_descr, sizeof(current_descr));
    responce.size = sizeof(current_descr);
  } else {
    responce.type = msg_type::GAME_OVER;
  }
  return responce;
}

void Game_Server::manage_client_buffer(QTcpSocket* socket, ServerBuffer& buffer) {
  switch (buffer.type) {
  case msg_type::GAME_BUFFER:
    auto responce = change_cpc(buffer,socket);
    start_sending_thread(socket->socketDescriptor(), buffer);
    break;
  case msg_type::GAME_INIT:
    auto cur_pleyer = players_lifes[socket];
    ServerBuffer tmp;
    memset(&tmp, 0, sizeof(ServerBuffer));
    tmp.type = msg_type::GAME_RESPONCE;
    tmp.size = sizeof(cur_pleyer);
    memcpy(&tmp.tankAction, &cur_pleyer, sizeof(cur_pleyer));
    start_sending_thread(socket->socketDescriptor(), tmp);
    break;
  }
}

ServerBuffer Game_Server::init_new_player(int socket_descriptior) {
  ServerBuffer tmp;
  memset(&tmp, 0, sizeof(ServerBuffer));
  tmp.type = msg_type::GAME_RESPONCE;
  //init_new_player
  QTcpSocket* new_player = new QTcpSocket();
  new_player->setSocketDescriptor(socket_descriptior);
  Player_condition np_cond = { 0 };
  np_cond.current_life = 10;
  players_lifes[new_player] = np_cond;
  QByteArray *buffer = new QByteArray();
  qint32 *s = new qint32(0);
  buffers.insert(new_player, buffer);
  sizes.insert(new_player, s);
  tmp.size = sizeof(Player_condition);
  memcpy(tmp.tankAction, &np_cond, sizeof(Player_condition));
  connect(new_player, &QTcpSocket::readyRead, this, &Game_Server::readyRead);
  return tmp;
}

void Game_Server::incomingConnection(qintptr socketDescriptor) {
  init_new_player(socketDescriptor);
  //start_sending_thread(socketDescriptor, tmp);
}
}//namespace game

