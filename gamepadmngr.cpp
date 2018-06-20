#include "gamepadmngr.h"
#include "iostream"

GamePadMngr::GamePadMngr(QObject *parent) : QObject(parent),m_gamepad(0) {
  m_gamepad = new QGamepad(0, this);//or just m_gamepad = new QGamepad; is ok//
  connect(m_gamepad, &QGamepad::connectedChanged, this, &GamePadMngr::connectedChangedEvent);
}

bool GamePadMngr::Is_connected() {
  return m_gamepad->isConnected();
}

void GamePadMngr::connectedChangedEvent(bool value) {
  if (value) {
    qDebug() << "Gamepad:: device is connect!";
  } else {
    qDebug() << "Gamepad:: device is disconnect!";
  }
}

void GamePadMngr::sendAction(Action buffer) {
  qDebug() << "Sending action to Tank Mngr";
}

void GamePadMngr::Listen_Input() {
  connect(m_gamepad, &QGamepad::buttonAChanged, this, [](bool pressed) {
    qDebug() << "Button A" << pressed;
  });
  connect(m_gamepad, &QGamepad::axisLeftXChanged, this, &GamePadMngr::axisLeftX_packet);
  connect(m_gamepad, &QGamepad::axisLeftYChanged, this, [](double value) {
    qDebug() << "Left Y" << value;
  });
  connect(m_gamepad, &QGamepad::axisRightXChanged, this, [](double value) {
    qDebug() << "Right X" << value;
  });
  connect(m_gamepad, &QGamepad::axisRightYChanged, this, [](double value) {
    qDebug() << "Right Y" << value;
  });

  connect(m_gamepad, &QGamepad::buttonBChanged, this, [](bool pressed) {
    qDebug() << "Button B" << pressed;
  });
  connect(m_gamepad, &QGamepad::buttonXChanged, this, [](bool pressed) {
    qDebug() << "Button X" << pressed;
  });
  connect(m_gamepad, &QGamepad::buttonYChanged, this, [](bool pressed) {
    qDebug() << "Button Y" << pressed;
  });
  connect(m_gamepad, &QGamepad::buttonL1Changed, this, [](bool pressed) {
    qDebug() << "Button L1" << pressed;
  });
  connect(m_gamepad, &QGamepad::buttonR1Changed, this, [](bool pressed) {
    qDebug() << "Button R1" << pressed;
  });
  connect(m_gamepad, &QGamepad::buttonL2Changed, this, [](double value) {
    qDebug() << "Button L2: " << value;
  });
  connect(m_gamepad, &QGamepad::buttonR2Changed, this, [](double value) {
    qDebug() << "Button R2: " << value;
  });
  connect(m_gamepad, &QGamepad::buttonSelectChanged, this, [](bool pressed) {
    qDebug() << "Button Select" << pressed;
  });
  connect(m_gamepad, &QGamepad::buttonStartChanged, this, [](bool pressed) {
    qDebug() << "Button Start" << pressed;
  });
  connect(m_gamepad, &QGamepad::buttonGuideChanged, this, [](bool pressed) {
    qDebug() << "Button Guide" << pressed;
  });

}

void GamePadMngr::axisLeftX_packet(double value) {
  qDebug() << "Left X" << value;
  //here create a packet init it
  Action buffer;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::buttonA_packet(bool pressed) {
  qDebug() << "Button A" << pressed;
}

void GamePadMngr::axisLeftY_packet(double value) {
  qDebug() << "Left Y" << value;
}

void GamePadMngr::buttonB_packet(bool pressed) {
  qDebug() << "Button B" << pressed;
}

void GamePadMngr::buttonX_packet(bool pressed) {
  qDebug() << "Button X" << pressed;
}
void GamePadMngr::buttonY_packet(bool pressed) {
  qDebug() << "Button Y" << pressed;
}
void GamePadMngr::buttonL1_packet(bool pressed) {
  qDebug() << "Button L1" << pressed;
}
void GamePadMngr::buttonR1_packet(bool pressed) {
  qDebug() << "Button R1" << pressed;
}
void GamePadMngr::buttonL2_packet(double value) {
  qDebug() << "Button L2: " << value;
}
void GamePadMngr::buttonR2_packet(double value) {
  qDebug() << "Button R2: " << value;
}
void GamePadMngr::buttonSelect_packet(bool pressed) {
  qDebug() << "Button Select" << pressed;
}
void GamePadMngr::buttonStart_packet(bool pressed) {
  qDebug() << "Button Start" << pressed;
}
void GamePadMngr::buttonGuide_packet(bool pressed) {
  qDebug() << "Button Guide" << pressed;
}

//connect(m_gamepad, &QGamepad::axisLeftXChanged, this, [](double value) {
//  qDebug() << "Left X" << value;
//});

GamePadMngr::~GamePadMngr() {
    delete m_gamepad;
}

