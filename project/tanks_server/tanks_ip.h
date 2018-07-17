#pragma once
#include <QTcpSocket>
#include <QNetworkSession>
#include <QtNetwork>
#include <QString>
const QHostAddress ip_tank_0("10.10.10.100");
const QHostAddress ip_tank_1("10.10.10.101");
const QHostAddress ip_tank_2("10.10.10.102");
const QHostAddress ip_tank_3("10.10.10.103");
const quint64 port_in = 34005;
const quint64 port_out = 34505;
const QString camera_url_1 = "http://test.test.com/1234890";