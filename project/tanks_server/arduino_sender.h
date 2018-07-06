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


extern std::map<action_type, std::string> command_dict;

class ArduinoSender:public QObject {
  Q_OBJECT
 public:
  ArduinoSender(Ui_MainWindow* gui, QHostAddress steel_ip = QHostAddress::Any,
    quint16 steel_port = port_in);
  bool Init(const QHostAddress steel_ip, quint16 steel_port);
  tank_status SendAction(std::string& packet);
 private:
  Ui_MainWindow* gui;
  QHostAddress steel_ip;
  quint16 steel_port;
  QTcpSocket *tcpSocket = nullptr;
  QByteArray IntToArray(qint32 source);
  QNetworkSession *networkSession = nullptr;
  QDataStream in;
  bool writeData(const std::string& data);
  public slots:
  bool connect_to_host();
  private slots:
  void readBuffer();
  void displayError(QAbstractSocket::SocketError socketError);
  void sessionOpened();
};
