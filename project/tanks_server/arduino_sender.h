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
 public slots:
  bool connect_to_host();
 signals:
  void tankDataReceived(ArduinoBuffer action);
 private slots:
  void newConnection();
  void disconnected();
  void readyRead();
 private:
  Ui_MainWindow* gui;
  QHostAddress steel_ip;
  quint16 steel_port_in;
  quint16 steel_port_out;
  QTcpSocket *tcpSocket = nullptr;
  QTcpSocket *socket_out = nullptr;
  QTcpServer *tcpServer = nullptr;
  QByteArray IntToArray(qint32 source);
  QNetworkSession *networkSession = nullptr;
  QDataStream in;
  bool connect_to_output();
  bool writeData(const std::string& data);
  QHash<QTcpSocket*, QByteArray*> buffers; //We need a buffer to store data until block has completely received
  QHash<QTcpSocket*, qint32*> sizes; //We need to store the size to verify if a block has received completely
 private slots:
  void readBuffer();
  void displayError(QAbstractSocket::SocketError socketError);
  void sessionOpened();

};
