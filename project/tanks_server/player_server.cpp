#include "player_server.h"
//TODO: realize close
namespace game{

QByteArray IntToArray(qint32 source) {
  //Avoid use of cast, this is the Qt way to serialize objects
  QByteArray temp;
  QDataStream data(&temp, QIODevice::ReadWrite);
  data << source;
  return temp;
}

  TankAction tk; //TODO: fix
qint32 ArrayToInt(QByteArray source) {
  qint32 temp;
  QDataStream data(&source, QIODevice::ReadWrite);
  data >> temp;
  return temp;
}
Player_server::Player_server(Ui_MainWindow* gui_): player_id(-1),gui(gui_) {
  QNetworkConfigurationManager manager;
  gui->comboBox->addItem("Tank 1");
  gui->comboBox->addItem("Tank 2");
  gui->comboBox->addItem("Tank 3");
  init_player_id();
  connect(gui->comboBox, &QComboBox::editTextChanged,
    this, &Player_server::init_player_id);
  connect(gui->pushButton, &QAbstractButton::clicked,
    this, &Player_server::StartServer);
  if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
    // Get saved network configuration
    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
    settings.endGroup();

    // If the saved network configuration is not currently discovered use the system default
    QNetworkConfiguration config = manager.configurationFromIdentifier(id);
    if ((config.state() & QNetworkConfiguration::Discovered) !=
      QNetworkConfiguration::Discovered) {
      config = manager.defaultConfiguration();
    }

    networkSession = new QNetworkSession(config, this);
    connect(networkSession, &QNetworkSession::opened, this, &Player_server::sessionOpened);

    gui->label->setText(tr("Opening network session."));
    networkSession->open();
  } else {
    sessionOpened();
  }
  camera_ip = camera_url_1;
  connect(tcpServer, &QTcpServer::newConnection, this, &Player_server::newConnection);
}

void Player_server::init_player_id() {
  auto user_choice = gui->comboBox->currentText();
  if (user_choice == "Tank 2") {
    player_id  = g_server_port_2;
  } else if (user_choice == "Tank 3") {
    player_id = g_server_port_3;
  } else {
    player_id = g_server_port_1;
  }
}

void Player_server::StartServer() {
  init_player_id();
  if (!tcpServer->listen(server_ip, player_id)) {
    qDebug() << "Unable to start the server: %1. " << tcpServer->errorString();
    //close();
    return;
  }
  gui->label->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n")
    .arg(server_ip.toString()).arg(tcpServer->serverPort()));
  gui->comboBox->hide();
  gui->pushButton->hide();
  gui->centralWidget->update();
  emit server_started(player_id);
}

void Player_server::sessionOpened() {
  // Save the used configuration
  if (networkSession) {
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
      id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
      id = config.identifier();
    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
  }
  tcpServer = new QTcpServer(this);
  QString ipAddress;
  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
  // use the first non-localhost IPv4 address
  for (int i = 0; i < ipAddressesList.size(); ++i) {
    if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
      ipAddress = ipAddressesList.at(i).toString();
      server_ip = ipAddressesList.at(i);
      break;
    }
  }

}

void Player_server::SendVideoToLocal(std::string camera_url) {
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_10);
  ServerBuffer buffer;
  memcpy(buffer.sender, server_ip.toString().data(), server_ip.toString().size());
  buffer.size = camera_url.size();
  buffer.type = msg_type::CAMERA_URL;
  memcpy(buffer.tankAction, camera_url.data(), buffer.size);
  out << buffer;
  sendBuffer(block);
}

bool Player_server::sendBuffer(QByteArray block) {
  if (socket->state() == QAbstractSocket::ConnectedState) {
    socket->write(IntToArray(block.size())); //write size of data
    socket->write(block); //write the data itself
    return socket->waitForBytesWritten();
  } else
    return false;
}

void Player_server::newConnection() {
  while (tcpServer->hasPendingConnections()) {
    socket = tcpServer->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead,this, &Player_server::readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Player_server::disconnected);
    SendVideoToLocal(camera_ip);
    QByteArray *buffer = new QByteArray();
    qint32 *s = new qint32(0);
    buffers.insert(socket, buffer);
    sizes.insert(socket, s);
    
  }
}

void Player_server::disconnected() {
  QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
  QByteArray *buffer = buffers.value(socket);
  qint32 *s = sizes.value(socket);
  socket->deleteLater();
  delete buffer;
  delete s;
}

void Player_server::ManageArduinoInfo() {
  return;
}

void Player_server::readyRead() {
  QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
  QByteArray *buffer = buffers.value(socket);
  qint32 *s = sizes.value(socket);
  qint32 size = *s;

  gui->player_out->appendPlainText("Started readyRead()");
  gui->centralWidget->update();
  gui->centralWidget->update();
  while (socket->bytesAvailable() > 0) {
    buffer->append(socket->readAll());
    //While can process data, process it
    gui->player_out->appendPlainText("Reading data");
    gui->centralWidget->update();
    while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size))  {
      //if size of data has received completely, then store it on our global variable
      if (size == 0 && buffer->size() >= 4) {
        size = ArrayToInt(buffer->mid(0, 4));
        *s = size;
        buffer->remove(0, 4);
      }
      gui->player_out->appendPlainText("Storing received data");
      gui->centralWidget->update();
      if (size > 0 && buffer->size() >= size) {
        QByteArray data = buffer->mid(0, size);
        buffer->remove(0, size);
        size = 0;
        *s = size;
        ServerBuffer buffer;
        memcpy(&buffer, data.data(), data.size());
          if (is_tank_action(buffer)) {
            memcpy(&tk, buffer.tankAction, sizeof(tk));
            gui->player_out->appendPlainText("Sending Tank Action with following data:");
            gui->player_out->appendPlainText("Type: " + QString::number((int)tk.type) + "; X value: "
              + QString::number(tk.x_value) + "; Y value:" + QString::number(tk.y_value));
            gui->centralWidget->update();
            emit tankDataReceived(tk);
          }
        //emit dataReceived(data);
      }
    }
  }
}
bool Player_server::is_tank_action(ServerBuffer buffer) {
  return buffer.type == msg_type::TANK_ACTION;
}
} //namespace game
