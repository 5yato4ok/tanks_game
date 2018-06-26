#ifndef PLAYER_H
#define PLAYER_H
#include <stdint.h>
#include <QtCore/qobject.h>
#include "action.h"
#include "game_type.h"
namespace game {
class Player_server: public QObject {
 public:
  Player_server();
  void AuthenticateWithSteel(int32_t player_id, int32_t tank_id);
  void GetGameAttributes(game_type type);
  void SendVideoToLocal();
  int32_t GetPlayerId() { return player_id; }
 signals:
  void SendSteelAction(TankAction action);
 public slots:
  void ManageArduinoInfo(); //Steel Info
private:
  void find_free_steel();
  int32_t player_id;
};
}
#endif // PLAYER_H
