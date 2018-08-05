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
#include "rules.h"
enum class player_type : int32_t {TANK,ROBOT, LAST};
enum class controler_type: int32_t {GAMEPAD, KEYBOARD,LAST};

//TODO: add threading

namespace client {

class Player_local: public QMainWindow {
  Q_OBJECT
 public:
  Player_local(QWidget *parent = Q_NULLPTR);

  void ChooseGame(game_type game_type = game_type::ONE_AGAINTS_ALL);
  void Authenticate(player_type player = player_type::TANK, 
    controler_type cntrl = controler_type::GAMEPAD);
  void GetCameraUrl();
  bool Connect_to_host(QString  ip,int32_t port);
 signals:
  void camera_ip_initilized();
  void is_authenticated();
  void hp_changed(Player_condition current_condition);
  void game_over(Player_condition current_condition);
 public slots:
  void readBuffer();
  void displayError(QAbstractSocket::SocketError socketError);
  void sessionOpened();
  void init_player_server_port(int32_t ip);
 protected:
  void SendActionsToServer(ServerBuffer buffer);
  std::string camera_ip;
  bool is_valid_network_session();
  bool is_autenticated_;
 private:
  void manage_game_over(const ServerBuffer& buffer);
  void manage_game_buffer(const ServerBuffer& buffer);
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
