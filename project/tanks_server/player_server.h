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
#include "ui_tanks_server.h"

namespace game {
class Player_server: public QMainWindow {
 public:
  Player_server(QMainWindow *parent = nullptr);
  void AuthenticateWithSteel(int32_t player_id, int32_t tank_id);
  void GetGameAttributes(game_type type);
  void SendVideoToLocal();
  int32_t GetPlayerId() { return player_id; }
 signals:
  void SendSteelAction(TankAction action);
 public slots:
  void ManageArduinoInfo(); //Steel Info
private:
  Ui_MainWindow* gui;
  void find_free_steel();
  int32_t player_id;
  QTcpServer *tcpServer = nullptr;
  QNetworkSession *networkSession = nullptr;
 private slots:
  void sessionOpened();
  void init_player_id();
  void sendBuffer();
};
}
#endif // PLAYER_H
