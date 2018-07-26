#pragma once
#include <QDataStream>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QtNetwork>
#include <QtCore/QTimer>
#include <QtWidgets/QMainWindow>
#include <stdint.h>
#include <string.h>
#include "game_type.h"
#include <QDebug>
#include "ui_Tanks_Client.h"
#include "server_settings.h"
#include "server_buffer.h"
#include <qbytearray.h>

enum class player_type : int32_t {TANK,ROBOT, LAST};
enum class controler_type: int32_t {GAMEPAD, KEYBOARD,LAST};

//TODO: add threading

namespace client {

class Player_local: public QMainWindow {
  Q_OBJECT
 public:
  Player_local(QWidget *parent = Q_NULLPTR);
  void SendActionsToServer(ServerBuffer& buffer);
  void ChooseGame(game_type game_type = game_type::ONE_AGAINTS_ALL);
  bool Authenticate(player_type player = player_type::TANK, 
    controler_type cntrl = controler_type::GAMEPAD);
  void ReDrawStreamingVideo();
  bool Connect_to_host(QString  ip,int32_t port);
 signals:
  void camera_ip_initilized();
 public slots:
  void readBuffer();
  void displayError(QAbstractSocket::SocketError socketError);
  void sessionOpened();
  void init_player_server_port(int32_t ip);
 protected:
  std::string camera_ip;
  bool is_valid_network_session();
 private:
  int32_t player_server_port;
  game_type choosed_game;
  const std::string password;
  QTcpSocket *tcpSocket = nullptr;
  QByteArray IntToArray(qint32 source);
  QNetworkSession *networkSession = nullptr;
  QMutex mutex;
  QDataStream in;
  void get_streaming_video();
  bool writeData(QByteArray data);
  void manage_input_buffer(const ServerBuffer& buffer);
  void init_camera_url(const ServerBuffer& buffer);
};

}
