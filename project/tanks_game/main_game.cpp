#include "game.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  game::Game game_mngr;
  game_mngr.show();
  return a.exec();
}
