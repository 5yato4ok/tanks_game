#include "player_server.h"
//TODO: realize close
namespace game{
Player_server::Player_server(QObject *parent): player_id(-1) {
}

void Player_server::init_player_id() {
  QRandomGenerator gen;
  player_id = gen.generate();
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
  if (!tcpServer->listen()) {
    qDebug() << "Unable to start the server: %1. " << tcpServer->errorString();
    //close();
    return;
  }
  QString ipAddress;
  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
  // use the first non-localhost IPv4 address
  for (int i = 0; i < ipAddressesList.size(); ++i) {
    if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
      ipAddressesList.at(i).toIPv4Address()) {
      ipAddress = ipAddressesList.at(i).toString();
      break;
    }
  }
  // if we did not find one, use IPv4 localhost
  if (ipAddress.isEmpty())
    ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
  //statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
  //  "Run the Tank Client example now.")
  //  .arg(ipAddress).arg(tcpServer->serverPort()));
}

void Player_server::sendBuffer() {
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_10);

  out << "Some test data. Player id"<<player_id;
  QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
  connect(clientConnection, &QAbstractSocket::disconnected,
    clientConnection, &QObject::deleteLater);

  clientConnection->write(block);
  clientConnection->disconnectFromHost();
}

} //namespace game
