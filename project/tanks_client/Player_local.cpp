#include "Player_local.h"

namespace client {
Player_local::Player_local(QWidget *parent) : QMainWindow(parent),
  password("pass"), tcpSocket(new QTcpSocket(this)) {
  choosed_game = game_type::ERROR_GAME;
  in.setDevice(tcpSocket);
  in.setVersion(QDataStream::Qt_5_10);
  connect(tcpSocket, &QIODevice::readyRead, this, &Player_local::readBuffer);
  connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
    this, &Player_local::displayError);
  QNetworkConfigurationManager manager;
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
    connect(networkSession, &QNetworkSession::opened, this, &Player_local::sessionOpened);
    qDebug()<<"Opening network session.";
    networkSession->open();
  }
}

bool Player_local::is_valid_network_session() {
  return !networkSession || networkSession->isOpen();
}

void Player_local::init_player_server_port(int32_t port) {
  player_server_port = port;
}

bool Player_local::Connect_to_host(const QString& ip, int32_t port) {
  tcpSocket->abort();
  tcpSocket->connectToHost(ip, port);
  return tcpSocket->waitForConnected();
}

void Player_local::readBuffer() {
   QByteArray input_buff;
   QString value;
  for (;;) {
    in.startTransaction();
    in >> input_buff;
    if (in.commitTransaction()) { 
      //qDebug() << "Received: " << input_buff;
      ServerBuffer buffer;
      memcpy(&buffer, input_buff.data(), sizeof(ServerBuffer));
      manage_input_buffer(buffer);
    } else {
      break;
    }
  }
}

void Player_local::init_camera_url(const ServerBuffer& buffer) {
  camera_ip = std::string(buffer.tankAction,buffer.size);
  emit camera_ip_initilized();
}

void Player_local::manage_input_buffer(const ServerBuffer& buffer) {
  switch (buffer.type) {
  case msg_type::CAMERA_URL:
    init_camera_url(buffer);
    break;
  case msg_type::GAME_BUFFER:
    break;
  default:
    break;
  }
}

void Player_local::ReDrawStreamingVideo() {
  get_streaming_video();
//and here comes some fun
}

void Player_local::SendActionsToServer(ServerBuffer& buffer) {
//sending buffer to server
  qDebug() << "Try to send data;";
  QByteArray packet;
  packet.resize(sizeof(buffer));
  memmove(packet.data(), &buffer, sizeof(buffer));
  writeData(packet);
}

void Player_local::get_streaming_video() {
//open cv connect by rhtcp
}

void Player_local::ChooseGame(game_type game_type) {
  choosed_game = game_type;
}

bool Player_local::Authenticate(player_type player, controler_type cntrl) {
//make here checking on which controller and player type
return true;
}

void Player_local::displayError(QAbstractSocket::SocketError socketError) {
  switch (socketError) {
  case QAbstractSocket::RemoteHostClosedError:
    break;
  case QAbstractSocket::HostNotFoundError:
    qDebug()<<"Tank Client"<<"The host was not found. Please check the "<<
        "host name and port settings.";
    break;
  case QAbstractSocket::ConnectionRefusedError:
    qDebug()<<"Tank Client. "<<
      "The connection was refused by the peer. "<<
        "Make sure the fortune server is running, "<<
        "and check that the host name and port "<<
        "settings are correct.";
    break;
  default:
    qDebug()<<"Fortune Client."<<"The following error occurred: "<<tcpSocket->errorString();
  }
}
void Player_local::sessionOpened() {
  // Save the used configuration
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

bool Player_local::writeData(QByteArray data) {
  if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
    tcpSocket->write(IntToArray(data.size())); //write size of data
    tcpSocket->write(data); //write the data itself
    return tcpSocket->waitForBytesWritten();
  } else
    return false;
}
//Use qint32 to ensure that the number have 4 bytes
QByteArray Player_local::IntToArray(qint32 source) {
  //Avoid use of cast, this is the Qt way to serialize objects
  QByteArray temp;
  QDataStream data(&temp, QIODevice::ReadWrite);
  data << source;
  return temp;
}

}// namespace client
