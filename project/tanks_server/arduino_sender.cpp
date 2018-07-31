#include "arduino_sender.h"

std::map<action_type, std::string> command_dict;

ArduinoSender::ArduinoSender(Ui_MainWindow* gui_, QHostAddress steel_ip_, quint16 steel_port_):
  tcpSocket(new QTcpSocket(this)), socket_out(new QTcpSocket(this)),gui(gui_), 
  steel_ip(steel_ip_),steel_port_in(steel_port_) {
  in.setDevice(tcpSocket);
  in.setVersion(QDataStream::Qt_5_10);
  connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
    this, &ArduinoSender::displayError);
  connect(socket_out, &QTcpSocket::readyRead, this, &ArduinoSender::readyRead);
}

void ArduinoSender::readyRead() {
  QByteArray data = socket_out->readAll();
  gui->arduino_out->appendPlainText("Arduino Manager: get info from steel:");
  gui->arduino_out->appendPlainText(data.data());
  std::string s_data = data.toStdString();
  //ArduinoBuffer buffer;
  //memcpy(&buffer, data.data(), data.size());
  emit tankDataReceived(s_data);
}

bool ArduinoSender::connect_to_host_out() {
  socket_out->abort();
  //socket_out->connectToHost("google.com", 80);
  //if (socket_out->waitForConnected())
  //  socket_out->write("HEAD / HTTP/1.0\r\n\r\n\r\n");
  socket_out->connectToHost(steel_ip, port_out);
  auto value =  socket_out->waitForConnected(1000);
  return value;
}

bool ArduinoSender::Init(const QHostAddress steel_ip_, quint16 steel_port_in_, quint16 steel_port_out_) {
  steel_ip = steel_ip_;
  steel_port_in = steel_port_in_;
  steel_port_out = steel_port_out_;
  return connect_to_host_in() && connect_to_host_out();
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


bool ArduinoSender::connect_to_host_in() {
  tcpSocket->abort();
  gui->arduino_out->appendPlainText("Arduino sender: connecting to " + steel_ip.toString());
  tcpSocket->connectToHost(steel_ip, steel_port_in);
  auto value = tcpSocket->waitForConnected(1000);
  return value;
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