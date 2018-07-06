#include "gamepadmngr.h"
#include "iostream"
namespace gp_helper {
GamePadMngr::GamePadMngr(QObject *parent) : QGamepad(0,parent){
  //m_gamepad = new QGamepad(0, this);//or just m_gamepad = new QGamepad; is ok//
  //auto list = m_gamepad->
  connect(this, &QGamepad::connectedChanged, this, &GamePadMngr::connectedChangedEvent);
}

bool GamePadMngr::Is_connected() {
  return QGamepad::isConnected();
}

void GamePadMngr::connectedChangedEvent(bool value) {
  if (value) {
    qDebug() << "Gamepad:: device is connect!";
  } else {
    qDebug() << "Gamepad:: device is disconnect!";
  }
}

//void GamePadMngr::sendAction(Raw_Action buffer) {
//  qDebug() << "Sending action";
//}

void GamePadMngr::Listen_Input() {
  connect(this, &QGamepad::buttonAChanged, this, &GamePadMngr::buttonA_packet);
  connect(this, &QGamepad::axisLeftXChanged, this, &GamePadMngr::axisLeftX_packet);
  //connect(this, &QGamepad::axisLeftYChanged, this, &GamePadMngr::axisLeftY_packet);
  connect(this, &QGamepad::axisRightXChanged, this, &GamePadMngr::axisRightX_packet);
  //connect(this, &QGamepad::axisRightYChanged, this, &GamePadMngr::axisRightY_packet);
  connect(this, &QGamepad::buttonBChanged, this, &GamePadMngr::buttonB_packet);
  connect(this, &QGamepad::buttonXChanged, this, &GamePadMngr::buttonX_packet);
  connect(this, &QGamepad::buttonYChanged, this, &GamePadMngr::buttonY_packet);
  connect(this, &QGamepad::buttonL1Changed, this, &GamePadMngr::buttonL1_packet);
  connect(this, &QGamepad::buttonR1Changed, this, &GamePadMngr::buttonR1_packet);
  connect(this, &QGamepad::buttonL2Changed, this, &GamePadMngr::buttonL2_packet);
  connect(this, &QGamepad::buttonR2Changed, this, &GamePadMngr::buttonR2_packet);
  connect(this, &QGamepad::buttonSelectChanged, this, &GamePadMngr::buttonSelect_packet);
  connect(this, &QGamepad::buttonStartChanged, this, &GamePadMngr::buttonStart_packet);
  connect(this, &QGamepad::buttonGuideChanged, this, &GamePadMngr::buttonGuide_packet);
  connect(this, &QGamepad::buttonUpChanged, this, &GamePadMngr::buttonUP_packet);
  connect(this, &QGamepad::buttonDownChanged, this, &GamePadMngr::buttonDOWN_packet);
  connect(this, &QGamepad::buttonLeftChanged, this, &GamePadMngr::buttonLEFT_packet);
  connect(this, &QGamepad::buttonRightChanged, this, &GamePadMngr::buttonRIGHT_packet);
}

void GamePadMngr::axisLeftX_packet(double value) {
  qDebug() << "Left X: " << value;
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_LEFT;
  buffer.value_x = value;
  buffer.value_y = QGamepad::axisLeftY();
  qDebug() << "Left Y: " << buffer.value_y;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::axisRightX_packet(double value) {
  qDebug() << "Right X: " << value;
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_RIGHT;
  buffer.value_x = value;
  buffer.value_y = QGamepad::axisRightY();
  qDebug() << "Right Y: " << buffer.value_y;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::axisRightY_packet(double value) {
  qDebug() << "Left Y" << value;
  
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_RIGHT;
  buffer.value_x= QGamepad::axisRightX();
  buffer.value_y = value;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::axisLeftY_packet(double value) {
  qDebug() << "Left Y" << value;
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_LEFT;
  buffer.value_x= QGamepad::axisLeftX();
  buffer.value_y = value;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::buttonA_packet(bool pressed) {
  qDebug() << "Button A" << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_A;
  buffer.is_pressed = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::buttonB_packet(bool pressed) {
  qDebug() << "Button B" << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_B;
  buffer.is_pressed = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::buttonX_packet(bool pressed) {
  qDebug() << "Button X" << pressed;
  
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_X;
  buffer.is_pressed = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonY_packet(bool pressed) {
  qDebug() << "Button Y" << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_Y;
  buffer.is_pressed = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonL1_packet(bool pressed) {
  qDebug() << "Button L1" << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_L1;
  buffer.is_pressed = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonR1_packet(bool pressed) {
  qDebug() << "Button R1" << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_R1;
  buffer.is_pressed = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonL2_packet(double value) {
  qDebug() << "Button L2: " << value;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_L2;
  buffer.value_x= value;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonR2_packet(double value) {
  qDebug() << "Button R2: " << value;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_R2;
  buffer.value_x= value;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonSelect_packet(bool pressed) {
  qDebug() << "Button Select" << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_SELECT;
  buffer.is_pressed = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonStart_packet(bool pressed) {
  qDebug() << "Button Start" << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_START;
  buffer.is_pressed = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonGuide_packet(bool pressed) {
  qDebug() << "Button Guide: " << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_GUIDE;
  buffer.is_pressed = pressed;
  emit sendAction(buffer); //TODO: check is it right?
}

void GamePadMngr::buttonUP_packet(bool value) {
  qDebug() << "Button UP: " << value;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_UP;
  buffer.is_pressed= value;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonDOWN_packet(bool pressed) {
  qDebug() << "Button DOWN: " << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_DOWN;
  buffer.is_pressed= pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonLEFT_packet(bool pressed) {
  qDebug() << "Button LEFT: " << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_LEFT;
  buffer.is_pressed= pressed;
  emit sendAction(buffer); //TODO: check is it right?
}
void GamePadMngr::buttonRIGHT_packet(bool pressed) {
  qDebug() << "Button RIGHT: " << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_RIGHT;
  buffer.is_pressed= pressed;
  emit sendAction(buffer); //TODO: check is it right?
}

GamePadMngr::~GamePadMngr() {
  //delete m_gamepad;
}
}//namespace gp_helper
