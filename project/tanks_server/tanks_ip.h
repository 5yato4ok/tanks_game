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

const std::string camera_url_1 = "rtsp://10.10.10.80/live1.264?user=admin&amp;passwd=";
const std::string camera_url_0 = "rtsp://10.10.10.81/live1.264?user=admin&amp;passwd=";
const std::string camera_url_2 = "rtsp://10.10.10.82/live1.264?user=admin&amp;passwd=";