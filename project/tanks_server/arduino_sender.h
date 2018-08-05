#pragma once
#include <QDataStream>
#include <QTcpSocket>
#include <QNetworkSession>
#include <QtNetwork>
#include "windows.h"
#include "WinSock.h"
#include "action.h"
#include <map>
#include <string>
#include "ui_tanks_server.h"
#include "tanks_ip.h"
#include "server_buffer.h"

extern std::map<action_type, std::string> command_dict;

class ArduinoSender:public QObject {
  Q_OBJECT
 public:
  ArduinoSender(Ui_MainWindow* gui, QHostAddress steel_ip = QHostAddress::Any,
    quint16 steel_port = port_in);
  bool Init(const QHostAddress steel_ip, quint16 steel_port_in, quint16 steel_port_out);
  tank_status SendAction(std::string& packet);
  
 signals:
  void ArdDataReceived(std::string action);
 private slots:
  void readyRead();
  void displayError(QAbstractSocket::SocketError socketError);
 private:
  bool connect_to_host_in();
  bool connect_to_host_out();
  Ui_MainWindow* gui;
  QHostAddress steel_ip;
  quint16 steel_port_in;
  quint16 steel_port_out;
  QTcpSocket *tcpSocket = nullptr;
  QTcpSocket *socket_out = nullptr;
  QByteArray IntToArray(qint32 source);
  QDataStream in;
  bool writeData(const std::string& data);

};
