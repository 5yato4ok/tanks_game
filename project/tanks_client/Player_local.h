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
 private:
  const int32_t user_id;
  game_type choosed_game;
  const std::string password;
  QTcpSocket *tcpSocket = nullptr;
  QByteArray IntToArray(qint32 source);
  QNetworkSession *networkSession = nullptr;
  QDataStream in;
  void get_streaming_video();
  bool writeData(QByteArray data);
 public slots:
  bool connect_to_host();
 private slots:
  void readBuffer();
  void displayError(QAbstractSocket::SocketError socketError);
  void sessionOpened();
};

}
