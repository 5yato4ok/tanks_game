#include "gamepadmngr.h"
#include "iostream"
#include <iomanip>
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
  //connect(this, &QGamepad::axisLeftXChanged, this, &GamePadMngr::axisLeftX_packet);
  //connect(this, &QGamepad::axisLeftYChanged, this, &GamePadMngr::axisLeftY_packet);
  connect(this, &QGamepad::axisRightXChanged, this, &GamePadMngr::axisRightX_packet);
  connect(this, &QGamepad::axisRightYChanged, this, &GamePadMngr::axisRightY_packet);
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

  connect(&thread, &GamePadThread::is_same, this, &GamePadMngr::button_is_pressed);
}

void GamePadMngr::Stop_Listen() {
  disconnect(this, &QGamepad::buttonAChanged, this, &GamePadMngr::buttonA_packet);
  //disconnect(this, &QGamepad::axisLeftXChanged, this, &GamePadMngr::axisLeftX_packet);
  //disconnect(this, &QGamepad::axisLeftYChanged, this, &GamePadMngr::axisLeftY_packet);
  disconnect(this, &QGamepad::axisRightXChanged, this, &GamePadMngr::axisRightX_packet);
  disconnect(this, &QGamepad::axisRightYChanged, this, &GamePadMngr::axisRightY_packet);
  disconnect(this, &QGamepad::buttonBChanged, this, &GamePadMngr::buttonB_packet);
  disconnect(this, &QGamepad::buttonXChanged, this, &GamePadMngr::buttonX_packet);
  disconnect(this, &QGamepad::buttonYChanged, this, &GamePadMngr::buttonY_packet);
  disconnect(this, &QGamepad::buttonL1Changed, this, &GamePadMngr::buttonL1_packet);
  disconnect(this, &QGamepad::buttonR1Changed, this, &GamePadMngr::buttonR1_packet);
  disconnect(this, &QGamepad::buttonL2Changed, this, &GamePadMngr::buttonL2_packet);
  disconnect(this, &QGamepad::buttonR2Changed, this, &GamePadMngr::buttonR2_packet);
  disconnect(this, &QGamepad::buttonSelectChanged, this, &GamePadMngr::buttonSelect_packet);
  disconnect(this, &QGamepad::buttonStartChanged, this, &GamePadMngr::buttonStart_packet);
  disconnect(this, &QGamepad::buttonGuideChanged, this, &GamePadMngr::buttonGuide_packet);
  disconnect(this, &QGamepad::buttonUpChanged, this, &GamePadMngr::buttonUP_packet);
  disconnect(this, &QGamepad::buttonDownChanged, this, &GamePadMngr::buttonDOWN_packet);
  disconnect(this, &QGamepad::buttonLeftChanged, this, &GamePadMngr::buttonLEFT_packet);
  disconnect(this, &QGamepad::buttonRightChanged, this, &GamePadMngr::buttonRIGHT_packet);
  disconnect(&thread, &GamePadThread::is_same, this, &GamePadMngr::button_is_pressed);
}

void GamePadMngr::axisLeftX_packet(double value) {
  qDebug() << "Left X: " << value;
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_LEFT;
  buffer.value_x = value;
  buffer.value_y = QGamepad::axisLeftY();
  qDebug() << "Left Y: " << buffer.value_y;
  thread.SetRawAction(buffer);
  thread.Start();
}

void GamePadMngr::axisRightX_packet(double value) {
  qDebug() << "Right X: " << value;
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_RIGHT;
  buffer.value_x = floor(value * (10)) / 10;
  if (buffer.value_x > 1) {
    buffer.value_x = 1;
  }  else if (buffer.value_x < -1) {
    buffer.value_x = -1;
  }
  //buffer.value_y = QGamepad::axisRightY();
  //qDebug() << "Right Y: " << buffer.value_y;
  //thread.SetRawAction(buffer);
  thread.SetAxis_x(buffer.value_x);
  thread.Start();
}

void GamePadMngr::axisRightY_packet(double value) {
  
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_RIGHT;
  //buffer.value_x= QGamepad::axisRightX();
  //qDebug() << "Right X" << buffer.value_x;
  qDebug() << "Right Y" << value;
  buffer.value_y = floor(value * (-10)) / 10; // For some reason value is inverted
  if (buffer.value_y > 1) {
    buffer.value_y = 1;
  } else if (buffer.value_y < -1) {
    buffer.value_y = -0.99;
  }
  if (buffer.value_y < 0.2 && buffer.value_y> 0) {
    buffer.value_y = 0;
  }
  if (buffer.value_y > -0.2 && buffer.value_y < 0) {
    buffer.value_y = 0;
  }
  //thread.SetRawAction(buffer);
  thread.SetAxis_y(buffer.value_y);
  thread.Start();
}

void GamePadMngr::axisLeftY_packet(double value) {
  qDebug() << "Left Y" << value;
  Raw_Action buffer;
  buffer.button = gp_buttons::AXIS_LEFT;
  buffer.value_x= QGamepad::axisLeftX(); 
  buffer.value_y = value;
  thread.SetRawAction(buffer);
  thread.Start();
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

void GamePadMngr::buttonUP_packet(bool pressed) {
  qDebug() << "Button UP: " << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_UP;
  buffer.is_pressed= pressed;
  thread.SetRawAction(buffer);
  thread.Start();
}
void GamePadMngr::buttonDOWN_packet(bool pressed) {
  qDebug() << "Button DOWN: " << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_DOWN;
  buffer.is_pressed= pressed;
  thread.SetRawAction(buffer);
  thread.Start();
}

void GamePadMngr::button_is_pressed(Raw_Action buffer) {
  thread.Exit();
  emit sendAction(buffer);
}

void GamePadMngr::buttonLEFT_packet(bool pressed) {
  qDebug() << "Button LEFT: " << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_LEFT;
  buffer.is_pressed = pressed;
  thread.SetRawAction(buffer);
  thread.Start();
}
void GamePadMngr::buttonRIGHT_packet(bool pressed) {
  qDebug() << "Button RIGHT: " << pressed;
  Raw_Action buffer;
  buffer.button = gp_buttons::BUT_RIGHT;
  buffer.is_pressed= pressed;
  thread.SetRawAction(buffer);
  thread.Start();
}

GamePadMngr::~GamePadMngr() {
  //delete m_gamepad;
}
}//namespace gp_helper
