#include <advertiser/masterserver_client.hpp>
#include <area/hub_manager.hpp>
#include <client/client_manager.hpp>
#include <configuration/config_manager.hpp>
#include <connection_handler.hpp>
#include <interfaces/network_socket_i.hpp>
#include <server.hpp>
#include <server_p.hpp>

#include <QDebug>

AkashiCore::Server::Server(int argc, char *argv[])
    : QCoreApplication(argc, argv)
    , d_ptr(std::make_unique<Private::ServerPrivate>())
{
  qDebug() << "[SERVER]::CTOR"
           << "Starting Server";
  d_ptr.get()->connection_handler = new AkashiNetwork::ConnectionHandler(this, ConfigManager::getInstance().serverPort(), ConfigManager::getInstance().wsServerPort());
  d_ptr.get()->client_manager = new AkashiCore::ClientManager(this);

  connect(d_ptr.get()->connection_handler, &AkashiNetwork::ConnectionHandler::newClientConnected, d_ptr.get()->client_manager, &ClientManager::on_newClientConnected);

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
    d_ptr.get()->masterserver_client = new AkashiNetwork::MasterserverClient(this, l_config);
  }

  d_ptr.get()->hub_manager = new AkashiArea::HubManager(this);
  d_ptr.get()->hub_manager->loadAreaList(ConfigManager::getInstance().readTextFile("config/areas.json"));
}

AkashiCore::Server::~Server()
{
  qDebug() << "[SERVER]::DTOR"
           << "Destroying Server";
}
