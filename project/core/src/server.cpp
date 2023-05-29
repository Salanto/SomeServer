#include <advertiser/masterserver_client.hpp>
#include <area/hub_manager.hpp>
#include <client/client_manager.hpp>
#include <configuration/config_manager.hpp>
#include <connection_handler.hpp>
#include <interfaces/network_socket_i.hpp>
#include <server.hpp>

#include <QDebug>
#include <QJsonDocument>

AkashiCore::Server::Server(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
  qDebug() << "[SERVER]::CTOR"
           << "Starting Server";

  connection_handler = new AkashiNetwork::ConnectionHandler(this, ConfigManager::getInstance().serverPort(), ConfigManager::getInstance().wsServerPort());

  hub_manager = new AkashiArea::HubManager(this);
  hub_manager->loadAreaList(ConfigManager::getInstance().readTextFile("config/areas.json"));

  client_manager = new AkashiCore::ClientManager(hub_manager, this);

  connect(connection_handler, &AkashiNetwork::ConnectionHandler::newClientConnected, client_manager, &ClientManager::on_newClientConnected);

  if (ConfigManager::getInstance().enableAdvertiser())
  {
    ConfigManager *config = &ConfigManager::getInstance();
    AkashiNetwork::MasterserverClient::MS_ClientConfig l_config;
    l_config.server_name = config->serverName();
    l_config.description = config->serverDescription();
    l_config.playercount = 0;
    l_config.port = config->serverPort();
    l_config.ws_port = config->wsServerPort();
    l_config.hostname = config->hostname();
    masterserver_client = new AkashiNetwork::MasterserverClient(this, l_config);
  }
}

AkashiCore::Server::~Server()
{
  qDebug() << "[SERVER]::DTOR"
           << "Destroying Server";
}
