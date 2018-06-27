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
#include <QCombobox>
#include <QLineEdit>
#include "ui_Tanks_Client.h"
#include "server_settings.h"
enum class player_type : int32_t {TANK,ROBOT, LAST};
enum class controler_type: int32_t {GAMEPAD, KEYBOARD,LAST};

namespace client {

class Player_local: public QMainWindow {
  Q_OBJECT
 public:
  Player_local(QWidget *parent = Q_NULLPTR);
  void SendActionsToServer();
  void ChooseGame(game_type game_type = game_type::ONE_AGAINTS_ALL);
  bool Authenticate(player_type player = player_type::TANK, 
    controler_type cntrl = controler_type::GAMEPAD);
  void ReDrawStreamingVideo();
 private:
  const int32_t user_id;
  game_type choosed_game;
  const std::string password;
  void get_streaming_video();
  QTcpSocket *tcpSocket = nullptr;
  QDataStream in;
  QNetworkSession *networkSession = nullptr;
 public slots:
  void request_player_id();
 private slots:
  void readBuffer();
  void displayError(QAbstractSocket::SocketError socketError);
  void sessionOpened();
};

}
