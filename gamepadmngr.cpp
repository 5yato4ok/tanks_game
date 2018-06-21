#include "gamepadmngr.h"
#include "iostream"
namespace gp_helper {
GamePadMngr::GamePadMngr(QObject *parent) : QObject(parent), m_gamepad(0){
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

void GamePadMngr::sendAction(Raw_Action buffer) {
  qDebug() << "Sending action";
}

void GamePadMngr::Listen_Input() {
  connect(m_gamepad, &QGamepad::buttonAChanged, this, [](bool pressed) {
    qDebug() << "Button A" << pressed;
  });
  connect(m_gamepad, &QGamepad::axisLeftXChanged, this, &GamePadMngr::axisLeftX_packet);
  connect(m_gamepad, &QGamepad::axisLeftYChanged, this, &GamePadMngr::axisLeftY_packet);
  connect(m_gamepad, &QGamepad::axisRightXChanged, this, &GamePadMngr::axisRightX_packet);
  connect(m_gamepad, &QGamepad::axisRightYChanged, this, &GamePadMngr::axisRightY_packet);
  connect(m_gamepad, &QGamepad::buttonBChanged, this, &GamePadMngr::buttonB_packet);
  connect(m_gamepad, &QGamepad::buttonXChanged, this, &GamePadMngr::buttonX_packet);
  connect(m_gamepad, &QGamepad::buttonYChanged, this, &GamePadMngr::buttonY_packet);
  connect(m_gamepad, &QGamepad::buttonL1Changed, this, &GamePadMngr::buttonL1_packet);
  connect(m_gamepad, &QGamepad::buttonR1Changed, this, &GamePadMngr::buttonR1_packet);
  connect(m_gamepad, &QGamepad::buttonL2Changed, this, &GamePadMngr::buttonL2_packet);
  connect(m_gamepad, &QGamepad::buttonR2Changed, this, &GamePadMngr::buttonR2_packet);
  connect(m_gamepad, &QGamepad::buttonSelectChanged, this, &GamePadMngr::buttonSelect_packet);
  connect(m_gamepad, &QGamepad::buttonStartChanged, this, &GamePadMngr::buttonStart_packet);
  connect(m_gamepad, &QGamepad::buttonGuideChanged, this, &GamePadMngr::buttonGuide_packet);

}

void GamePadMngr::axisLeftX_packet(double value) {
  qDebug() << "Left X" << value;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_LEFT;
  buffer.value = value;
  buffer.x = true;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::axisRightX_packet(double value) {
  qDebug() << "Right X" << value;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_RIGHT;
  buffer.value = value;
  buffer.x = true;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::axisRightY_packet(double value) {
  qDebug() << "Left Y" << value;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_RIGHT;
  buffer.value = value;
  buffer.x = false;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::axisLeftY_packet(double value) {
  qDebug() << "Left Y" << value;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_LEFT;
  buffer.value = value;
  buffer.x = false;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::buttonA_packet(bool pressed) {
  qDebug() << "Button A" << pressed;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_A;
  buffer.value = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::buttonB_packet(bool pressed) {
  qDebug() << "Button B" << pressed;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_B;
  buffer.value = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::buttonX_packet(bool pressed) {
  qDebug() << "Button X" << pressed;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_X;
  buffer.value = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonY_packet(bool pressed) {
  qDebug() << "Button Y" << pressed;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_Y;
  buffer.value = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonL1_packet(bool pressed) {
  qDebug() << "Button L1" << pressed;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_L1;
  buffer.value = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonR1_packet(bool pressed) {
  qDebug() << "Button R1" << pressed;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_R1;
  buffer.value = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonL2_packet(double value) {
  qDebug() << "Button L2: " << value;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_L2;
  buffer.value = value;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonR2_packet(double value) {
  qDebug() << "Button R2: " << value;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_R2;
  buffer.value = value;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonSelect_packet(bool pressed) {
  qDebug() << "Button Select" << pressed;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_SELECT;
  buffer.value = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonStart_packet(bool pressed) {
  qDebug() << "Button Start" << pressed;
  //here create a packet init it
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_START;
  buffer.value = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonGuide_packet(bool pressed) {
  qDebug() << "Button Guide" << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_GUIDE;
  buffer.value = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}

GamePadMngr::~GamePadMngr() {
  delete m_gamepad;
}
}//namespace gp_helper
