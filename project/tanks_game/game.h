#pragma once
#include "game_server.h"
#include <QMainwindow>
namespace game {
class Game : public QMainWindow {
  Q_OBJECT
 public:
  Game::Game(QMainWindow* parent = nullptr);
  void Manage_P2P_Action();
 private:
  QNetworkSession *networkSession = nullptr;
  Game_Server server;
  void set_rules(game_type type);
  int32_t get_players_id();
 private slots:
  void sessionOpened();
};

}//namesapce game
