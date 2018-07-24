#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_tanks_game.h"

class tanks_game : public QMainWindow
{
    Q_OBJECT

public:
    tanks_game(QWidget *parent = Q_NULLPTR);

private:
    Ui::tanks_gameClass ui;
};
