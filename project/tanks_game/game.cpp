#include "game.h"

namespace game {
Game::Game(QMainWindow* parent):QMainWindow(parent),gui(new Ui_tanks_gameClass){
  gui->setupUi(this);
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
    connect(networkSession, &QNetworkSession::opened, this, &Game::sessionOpened);

    gui->label->setText(tr("Opening network session."));
    networkSession->open();
  } else {
    sessionOpened();
  }
}

void Game::sessionOpened() {
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

  // use the first non-localhost IPv4 address
  QHostAddress ip (g_server_ip);
  if (!server.listen(ip, g_game_port)) {
    qDebug() << "Unable to start the server: %1. " << server.errorString();
    //close();
    return;
  }
  gui->label->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
    "Run the Tank Client example now.")
    .arg(ip.toString()).arg(g_game_port));
  gui->centralWidget->update();
}

} //namespace game
