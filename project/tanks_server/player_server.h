#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>
#include <QtCore>
#include <Qvector>
#include "action.h"
#include "game_type.h"
#include <QtNetwork>
#include <qdatastream.h>
#include "server_buffer.h"
#include "server_settings.h"
#include "ui_tanks_server.h"
#include "tanks_ip.h"
//TODO: make gui global as separate debug class
namespace game {
class Player_server: public QObject {
  Q_OBJECT
 public:
  Player_server(Ui_MainWindow* gui);
  ~Player_server();
  void AuthenticateWithSteel(int32_t player_id, int32_t tank_id);

  void SendVideoToLocal();
  int32_t GetPlayerId() { return player_id; }
 signals:
  void tankDataReceived(TankAction action);
  void dataReceived(QByteArray);
  void server_started(int32_t player_id);
  void new_player();
 public slots:
  void StartServer();
 protected:
  Ui_MainWindow* gui;
  void ManageArduinoInfo(ServerBuffer& buffer); //Steel Info
  void redirect_game_action(ServerBuffer& buffer);
 private:
   void redirect_responce(ServerBuffer& buffer);
  bool connect_to_game_server();
  void get_game_attributes(game_type type = game_type::ONE_AGAINTS_ALL);
  void send_data_to_game_server();
  void manage_client_buffer(ServerBuffer& buffer);
  QHostAddress server_ip;
  QTcpSocket *socket_client = nullptr;
  QTcpSocket *socket_game = nullptr;
  int32_t player_id;
  std::string camera_ip;
  QString game_ip;
  quint16 game_port;
  QTcpServer *tcpServer = nullptr;
  QNetworkSession *networkSession = nullptr;
  QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
  QHash<QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely
  //game_attributes
 private slots:
  void sessionOpened();
  void init_player_id();
  bool sendBuffer(QByteArray block, QTcpSocket* socket_s);
  void disconnected();
  void readyRead();
  void newConnection();
};
}
#endif // PLAYER_H
