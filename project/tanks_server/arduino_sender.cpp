#include "arduino_sender.h"

std::map<action_type, std::string> command_dict;

ArduinoSender::ArduinoSender(Ui_MainWindow* gui_, QHostAddress steel_ip_, quint16 steel_port_):
  tcpSocket(new QTcpSocket(this)), gui(gui_) , steel_ip(steel_ip_),steel_port_in(steel_port_),
  tcpServer(new QTcpServer(this))
{
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
    gui->arduino_out->appendPlainText("Arduino sender: Opening network session.");
    gui->centralWidget->update();
    networkSession->open();
  }
  connect(tcpServer, &QTcpServer::newConnection, this, &ArduinoSender::newConnection);
}

void ArduinoSender::disconnected() {
  QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
  QByteArray *buffer = buffers.value(socket);
  qint32 *s = sizes.value(socket);
  socket->deleteLater();
  delete buffer;
  delete s;
}

void ArduinoSender::readyRead() {
  QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
  QByteArray *buffer = buffers.value(socket);
  qint32 *s = sizes.value(socket);
  qint32 size = *s;

  gui->arduino_out->appendPlainText("ArduinoSender::Started readyRead()");
  gui->centralWidget->update();
  gui->centralWidget->update();
  while (socket->bytesAvailable() > 0) {
    buffer->append(socket->readAll());
    //While can process data, process it
    gui->arduino_out->appendPlainText("ArduinoSender::Reading data");
    gui->centralWidget->update();
    while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) {
      //if size of data has received completely, then store it on our global variable
      if (size == 0 && buffer->size() >= 4) {
        size = ArrayToInt(buffer->mid(0, 4));
        *s = size;
        buffer->remove(0, 4);
      }
      gui->arduino_out->appendPlainText("ArduinoSender::Storing received data");
      gui->centralWidget->update();
      if (size > 0 && buffer->size() >= size) {
        QByteArray data = buffer->mid(0, size);
        buffer->remove(0, size);
        size = 0;
        *s = size;
        ArduinoBuffer buffer;
        memcpy(&buffer, data.data(), data.size());
        emit tankDataReceived(buffer);
      }
    }
  }
}

void ArduinoSender::newConnection() {
  while (tcpServer->hasPendingConnections()) {
    socket_out = tcpServer->nextPendingConnection();
    connect(socket_out, &QTcpSocket::readyRead, this, &ArduinoSender::readyRead);
    connect(socket_out, &QTcpSocket::disconnected, this, &ArduinoSender::disconnected);
    QByteArray *buffer = new QByteArray();
    qint32 *s = new qint32(0);
    buffers.insert(socket_out, buffer);
    sizes.insert(socket_out, s);
  }
}

bool ArduinoSender::connect_to_output() {
  return tcpServer->listen(steel_ip, steel_port_out);
}

bool ArduinoSender::Init(const QHostAddress steel_ip_, quint16 steel_port_in_, quint16 steel_port_out_) {
  steel_ip = steel_ip_;
  steel_port_in = steel_port_in_;
  steel_port_out = steel_port_out_;
  return connect_to_host(); // &&connect_to_output();
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
  gui->arduino_out->appendPlainText("Arduino sender: Sending Data to Steel");
  if (writeData(packet)) {
    gui->arduino_out->appendPlainText("Arduino sender: Sending Data to Steel Success");
    return tank_status::OPPERATION_SUCCESS;
  } else {
    gui->arduino_out->appendPlainText("Arduino sender: Sending Data to Steel Error");
  }
  gui->centralWidget->update();
  return tank_status::OPERATION_FAILED;
}


bool ArduinoSender::connect_to_host() {
  tcpSocket->abort();
  gui->arduino_out->appendPlainText("Arduino sender: connecting to " + steel_ip.toString());
  tcpSocket->connectToHost(steel_ip, steel_port_in);
  return tcpSocket->waitForConnected(1000);
}

void ArduinoSender::readBuffer() {
  //in.startTransaction();

  QString input_buff;
  //in >> input_buff;
  for (;;) {
    in.startTransaction();
    in >> input_buff;
    if (in.commitTransaction())
      gui->arduino_out->appendPlainText("Received: " + input_buff);
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
    gui->arduino_out->appendPlainText("Arduino Sender\n The host was not found.");
    gui->arduino_out->appendPlainText("Please check the \n host name and port settings.");
    break;
  case QAbstractSocket::ConnectionRefusedError:
    gui->arduino_out->appendPlainText("Arduino Sender ");
    gui->arduino_out->appendPlainText("The connection was refused by the peer. ");
    gui->arduino_out->appendPlainText("Make sure the fortune server is running, ");
    gui->arduino_out->appendPlainText("and check that the host name and port ");
    gui->arduino_out->appendPlainText("settings are correct.");
    break;
  default:
    gui->arduino_out->appendPlainText("Arduino Sender. The following error occurred: ");
    gui->arduino_out->appendPlainText(tcpSocket->errorString());
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