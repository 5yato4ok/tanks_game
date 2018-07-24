#pragma once
#include "game_server.h"
#include "ui_tanks_game.h"
#include <QMainWindow>
namespace game {
class Game : public QMainWindow {
  Q_OBJECT
 public:
  Game::Game(QMainWindow* parent = nullptr);
  void Manage_P2P_Action();
 private:
  Ui_tanks_gameClass* gui;
  QNetworkSession *networkSession = nullptr;
  Game_Server server;
  void set_rules(game_type type);
  int32_t get_players_id();
 private slots:
  void sessionOpened();
};

}//namesapce game
