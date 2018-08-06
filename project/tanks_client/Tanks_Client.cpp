#include "Tanks_Client.h"
namespace client {
Tanks_Client::Tanks_Client(QMainWindow *parent) : Player_local(parent),
 ui(new Ui::Tanks_ClientClass),camera(ui,parent), can_shoot(true), timer(30000){
  set_gui();
  connect(ui->comboBox, &QComboBox::editTextChanged, this, &Tanks_Client::enable_reconnect_button);
  connect(ui->connect_server, &QAbstractButton::clicked,this, &Tanks_Client::reconnect);
  connect(this, &Player_local::is_authenticated, this, &Tanks_Client::Connect_signals);

  get_default_buttons_settings();

}

void Tanks_Client::show_debug_window() {
  if (ui->output->isHidden()) {
    ui->output->show();
    ui->logo->hide();
  } else {
    ui->output->hide();
    ui->logo->show();
  }
}

void Tanks_Client::set_gui() {
  ui->setupUi(this);
  ui->comboBox->addItem("Tank 0");
  ui->comboBox->addItem("Tank 1");
  ui->comboBox->addItem("Tank 2");
  ui->output->hide();
  ui->connect_server->setDefault(true);
  ui->gameState->setReadOnly(true);
  gun_shot.setSource(QUrl::fromLocalFile("gun_shot.wav"));
  gun_shot.setVolume(0.25f);
  ui->logo->setAlignment(Qt::AlignCenter);
  ui->logo->setPixmap(QPixmap("logo.png"));//.scaled(ui->output->size()));
  ui->logo_name->setPixmap(QPixmap("logo_name.png"));
  connect(ui->debugButton, &QPushButton::clicked, this, &Tanks_Client::show_debug_window);

}

void Tanks_Client::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);
  ui->layoutWidget->resize(event->size());
  //ui->layoutWidget->resizeEvent(event);
}

void Tanks_Client::change_hp(Player_condition current_condition) {
  std::string hitted_by(current_condition.hitted_by, current_condition.size);
  ui->gameState->appendPlainText("HP:"+QString::number(current_condition.current_life));
  if (hitted_by.size()) {
    ui->gameState->appendPlainText("Was hitted by: " + QString::fromStdString(hitted_by));
  }
}

void Tanks_Client::enable_reconnect_button() {
  ui->connect_server->setEnabled(is_valid_network_session() &&
    !ui->comboBox->currentText().isEmpty());
}

void Tanks_Client::reconnect() {
  auto user_choice = ui->comboBox->currentText();
  ui->gameState->clear();
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
    Player_local::GetCameraUrl();
  }
}

void Tanks_Client::load_video() {
  camera.StopVideo();
  camera.LoadVideo(Player_local::camera_ip);
}

void Tanks_Client::start_video() {
  camera.StartVideo();
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

void Tanks_Client::change_can_shot() {
  can_shoot = true;
  ui->gameState->appendPlainText("Reloading complited");
}

void Tanks_Client::start_shot_timer() {
  timer.Exit();
  timer.Start();
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
  switch (supported_buttons[buffer.button]) {
  case (int)action_type::MOVE_TRACK:
    ui->output->appendPlainText("\nIs track action:\n X" + QString::number(buffer.value_x) +
      "Y: " + QString::number(buffer.value_y));
    send_action(action);
    break;
  case (int)action_type::MOVE_TOWER_RIGHT:
  case (int)action_type::MOVE_TOWER_LEFT:
  case (int)action_type::MOVE_GUN_UP:
  case (int)action_type::MOVE_GUN_DOWN:
    ui->output->appendPlainText("\nIs tower action");
    send_action(action);
    break;
  case (int)action_type::SHOT:
    ui->output->appendPlainText("\nIs gun action");
    if (can_shoot) {
      can_shoot = false;
      send_action(action);
      start_shot_timer();
      gun_shot.play();
    } else {
      ui->gameState->appendPlainText("Gun: Reloading");
    }
    break;
  }

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
  Disconnect_signals();
  connect(&gamepad, SIGNAL(sendAction(Raw_Action)), this,SLOT(ReceiveData(Raw_Action)));
  connect(this, &Player_local::camera_ip_initilized, this, &Tanks_Client::load_video);
  connect(&camera, &Camera::video_loaded, this, &Tanks_Client::start_video);
  connect(this, &Player_local::hp_changed, this, &Tanks_Client::change_hp);
  connect(this, &Player_local::game_over, this, &Tanks_Client::game_over);
  connect(&timer, &TimerThread::exit_timer, this, &Tanks_Client::change_can_shot);
  gamepad.Listen_Input();
}

void Tanks_Client::game_over(Player_condition current_condition) {
  ui->gameState->appendPlainText("Game_over!");
  ui->connect_server->setEnabled(true);
}

void Tanks_Client::Disconnect_signals() {
  disconnect(&gamepad, SIGNAL(sendAction(Raw_Action)), this,SLOT(ReceiveData(Raw_Action)));
  disconnect(this, &Player_local::camera_ip_initilized, this, &Tanks_Client::load_video);
  disconnect(this, &Player_local::hp_changed, this, &Tanks_Client::change_hp);
  disconnect(&camera, &Camera::video_loaded, this, &Tanks_Client::start_video);
  disconnect(this, &Player_local::camera_ip_initilized, this, &Tanks_Client::load_video);
  disconnect(&timer, &TimerThread::exit_timer, this, &Tanks_Client::change_can_shot);
  gamepad.Stop_Listen();
}
  
}//namespace client
