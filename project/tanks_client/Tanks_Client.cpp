#include "Tanks_Client.h"
namespace client {
Tanks_Client::Tanks_Client(QWidget *parent) : Player_local(parent),
 ui(new Ui::Tanks_ClientClass),camera(ui,parent){
  ui->setupUi(this);
  ui->comboBox->addItem("Tank 0");
  ui->comboBox->addItem("Tank 1");
  ui->comboBox->addItem("Tank 2");
  ui->connect_server->setDefault(true);
  connect(ui->comboBox, &QComboBox::editTextChanged, this, &Tanks_Client::enable_reconnect_button);
  connect(ui->connect_server, &QAbstractButton::clicked,this, &Tanks_Client::reconnect);
  connect(this, &Player_local::is_authenticated, this, &Tanks_Client::Connect_signals);
  get_default_buttons_settings();
}

void Tanks_Client::change_hp(Player_condition current_condition) {
  std::string hitted_by(current_condition.hitted_by, current_condition.size);
  ui->gameState->appendPlainText(QString::number(current_condition.current_life));
  ui->gameState->appendPlainText("Was hitted by: " + QString::fromStdString(hitted_by));
}

void Tanks_Client::enable_reconnect_button() {
  ui->connect_server->setEnabled(is_valid_network_session() &&
    !ui->comboBox->currentText().isEmpty());
}
void Tanks_Client::reconnect() {
  auto user_choice = ui->comboBox->currentText();
  int32_t port;
  if (user_choice == "Tank 0") {
    port = g_server_port_0;
  } else if (user_choice == "Tank 1") {
    port = g_server_port_1;
  } else {
    port = g_server_port_2;
  }
  if (Connect_to_host(g_server_ip, port)) {
    ui->comboBox->hide(); //we can enable only to one player
    ui->connect_server->setText("Reconnect");
    Player_local::Authenticate();
  }
}

void Tanks_Client::load_video() {
  camera.StopVideo();
  //if (camera.LoadVideo(Player_local::camera_ip)) {
  //  camera.StartVideo();
  //}
}

gp_helper::Button_settings Tanks_Client::Init_User_Buttons(gp_helper::Button_settings user_def) {
  auto previos_setting = supported_buttons;
  supported_buttons = user_def;
  return previos_setting;
}
bool Tanks_Client::get_default_buttons_settings() {
  return false;
}
bool Tanks_Client::is_tank_action(Raw_Action& buffer) {
  for (auto& sp_button : supported_buttons) {
    if (sp_button.first == buffer.button) {
      return true;
    }
  }
  return false;
}

void Tanks_Client::ReceiveData(Raw_Action buffer) {
  //qDebug() << "Tank: Received Data";
  ui->output->appendPlainText("\nTank: Received Data");
  if (!is_tank_action(buffer)) {
    return;
  }
  TankAction action;
  action.type = (action_type)supported_buttons[buffer.button];
  action.x_value = buffer.value_x;
  action.y_value = buffer.value_y;
  action.is_pressed = buffer.is_pressed;
  if (supported_buttons[buffer.button] == (int)action_type::MOVE_TRACK) {
    ui->output->appendPlainText("\nIs track action:\n X" + QString::number(buffer.value_x)+ 
    "Y: " + QString::number(buffer.value_y));
  } else if (supported_buttons[buffer.button] == (int)action_type::MOVE_TOWER_RIGHT||
    supported_buttons[buffer.button] == (int)action_type::MOVE_TOWER_LEFT ||
    supported_buttons[buffer.button] == (int)action_type::MOVE_GUN_UP || 
    supported_buttons[buffer.button] == (int)action_type::MOVE_GUN_DOWN) {
    ui->output->appendPlainText("\nIs tower action");
  } else if (supported_buttons[buffer.button] == (int)action_type::SHOT) {
    ui->output->appendPlainText("\nIs gun action");
  }
  send_action(action);
  return;
}

void Tanks_Client::send_action(TankAction buffer) {
  ServerBuffer packet;
  ui->output->appendPlainText(QTime::currentTime().toString() +": Sending action");
  packet.size = sizeof(TankAction);
  packet.type =msg_type::TANK_ACTION;
  memcpy(packet.tankAction, &buffer, sizeof(TankAction));
  Player_local::SendActionsToServer(packet);
}

void Tanks_Client::Connect_signals() {
  connect(&gamepad, SIGNAL(sendAction(Raw_Action)), this,SLOT(ReceiveData(Raw_Action)));
  connect(this, &Player_local::camera_ip_initilized, this, &Tanks_Client::load_video);
  connect(this, &Player_local::hp_changed, this, &Tanks_Client::change_hp);
  gamepad.Listen_Input();
}

void Tanks_Client::Disconnect_signals() {
  disconnect(&gamepad, SIGNAL(sendAction(Raw_Action)), this,
    SLOT(ReceiveData(Raw_Action)));
  disconnect(this, &Player_local::camera_ip_initilized, this, 
    &Tanks_Client::load_video);
}
  
}//namespace client
