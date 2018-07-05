#include "arduino_sender.h"

std::map<action_type, std::string> command_dict;

ArduinoSender::ArduinoSender(Ui_MainWindow* gui_):
  tcpSocket(new QTcpSocket(this)), gui(gui_) {
  in.setDevice(tcpSocket);
  in.setVersion(QDataStream::Qt_5_10);

  connect(tcpSocket, &QIODevice::readyRead, this, &ArduinoSender::readBuffer);
  connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
    this, &ArduinoSender::displayError);
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
    connect(networkSession, &QNetworkSession::opened, this, &ArduinoSender::sessionOpened);
    gui->output->appendPlainText("Arduino sender: Opening network session.");
    networkSession->open();
  }
}

bool ArduinoSender::writeData(const std::string& data) {
  if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
    //tcpSocket->write(IntToArray(data.size())); //write size of data
    //tcpSocket->write(data); //write the data itself
    tcpSocket->write(data.data(), data.size());
    return tcpSocket->waitForBytesWritten();
  } else
    return false;
}

tank_status ArduinoSender::SendAction(std::string& packet) {
  gui->output->appendPlainText("Arduino sender: Sending Data to Steel");
  if (connect_to_host() && writeData(packet)) {
    gui->output->appendPlainText("Arduino sender: Sending Data to Steel Success");
    return tank_status::OPPERATION_SUCCESS;
  } else {
    gui->output->appendPlainText("Arduino sender: Sending Data to Steel Error");
  }
  return tank_status::OPERATION_FAILED;
}


bool ArduinoSender::connect_to_host() {
  tcpSocket->abort();
  tcpSocket->connectToHost(tank_ip, tank_port);
  return tcpSocket->waitForConnected();
}

void ArduinoSender::readBuffer() {
  //in.startTransaction();

  QString input_buff;
  //in >> input_buff;

  for (;;) {
    in.startTransaction();
    in >> input_buff;
    if (in.commitTransaction())
      qDebug() << "Received: " << input_buff;
    else
      break;
  }
}

QByteArray ArduinoSender::IntToArray(qint32 source) {
  //Avoid use of cast, this is the Qt way to serialize objects
  QByteArray temp;
  QDataStream data(&temp, QIODevice::ReadWrite);
  data << source;
  return temp;
}

void ArduinoSender::displayError(QAbstractSocket::SocketError socketError) {
  switch (socketError) {
  case QAbstractSocket::RemoteHostClosedError:
    break;
  case QAbstractSocket::HostNotFoundError:
    qDebug() << "Tank Client" << "The host was not found. Please check the " <<
      "host name and port settings.";
    break;
  case QAbstractSocket::ConnectionRefusedError:
    qDebug() << "Tank Client. " <<
      "The connection was refused by the peer. " <<
      "Make sure the fortune server is running, " <<
      "and check that the host name and port " <<
      "settings are correct.";
    break;
  default:
    qDebug() << "Fortune Client." << "The following error occurred: " << tcpSocket->errorString();
  }
}
void ArduinoSender::sessionOpened() {
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