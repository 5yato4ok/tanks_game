#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>
#include <QtCore/qobject.h>
#include <QtCore/qsettings.h>
#include <Qvector>
#include "action.h"
#include "game_type.h"
#include "QtNetwork/qnetworkconfigmanager.h"
#include "QtNetwork/qtcpserver.h"
#include "QtNetwork/qtcpsocket.h"
#include "QtNetwork/qnetworksession.h"
#include "qrandom.h"
#include "qdatastream.h"
#include "server_buffer.h"
#include "ui_tanks_server.h"
//TODO: make gui global
namespace game {
class Player_server: public QObject {
  Q_OBJECT
 public:
  Player_server(Ui_MainWindow* gui);
  void AuthenticateWithSteel(int32_t player_id, int32_t tank_id);
  void GetGameAttributes(game_type type);
  void SendVideoToLocal();
  int32_t GetPlayerId() { return player_id; }
 signals:
  void tankDataReceived(TankAction action);
  void dataReceived(QByteArray);
 public slots:
  void ManageArduinoInfo(); //Steel Info
 protected:
  Ui_MainWindow* gui;
 private:
  void find_free_steel();
  bool is_tank_action(ServerBuffer buffer);
  int32_t player_id;
  QTcpServer *tcpServer = nullptr;
  QNetworkSession *networkSession = nullptr;
  QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
  QHash<QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely
 private slots:
  void sessionOpened();
  void init_player_id();
  void sendBuffer();
  void disconnected();
  void readyRead();
  void newConnection();
};
}
#endif // PLAYER_H
