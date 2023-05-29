#include "client_manager.hpp"
#include "client/client.hpp"
#include "client/client_manager_p.hpp"
#include "client/client_packet_handler.hpp"
#include "configuration/config_manager.hpp"
#include "interfaces/network_socket_i.hpp"
#include "packets/custom_packet.hpp"

#include <QDebug>

using namespace AkashiCore;

ClientManager::ClientManager(AkashiArea::HubManager *hub_manager, QObject *parent)
    : QObject(parent)
    , d_ptr(std::make_unique<Private::ClientManagerPrivate>())
{
  qDebug() << "[ClientManager]::CTOR"
           << "Starting ClientManager";

  d_ptr.get()->hub_manager = hub_manager;

  int max_players = ConfigManager::getInstance().maxPlayers();
  for (int i = max_players; i >= 0; i--)
  {
    d_ptr.get()->player_ids.push(i);
  }
}

ClientManager::~ClientManager()
{
  qDebug() << "[ClientManager]::DTOR"
           << "Destroying ClientManager";
}

void ClientManager::on_newClientConnected(AkashiNetwork::NetworkSocket *l_socket)
{
  if (d_ptr.get()->player_ids.isEmpty())
  {
    AkashiNetwork::PacketCustom packet("KB", {"TOOMANYPLAYERS"});
    l_socket->writeData(packet.toUtf8());
    l_socket->deleteLater();
    return;
  }

  int player_id = d_ptr.get()->player_ids.pop();
  auto l_client = new Client(this, l_socket, player_id);
  d_ptr.get()->clients.insert(player_id, l_client);

  auto l_client_handler = new ClientPacketHandler(l_client, l_socket, d_ptr.get()->hub_manager, this);
  d_ptr.get()->client_handlers.insert(player_id, l_client_handler);
  l_client_handler->handshake();

  connect(l_client, &Client::clientDisconnected, this, &ClientManager::on_clientDisconnected);
}

void ClientManager::on_clientDisconnected(int f_client_id)
{
  d_ptr.get()->clients[f_client_id]->deleteLater();
  d_ptr.get()->clients.remove(f_client_id);
  d_ptr.get()->client_handlers[f_client_id]->deleteLater();
  d_ptr.get()->client_handlers.remove(f_client_id);
  d_ptr.get()->player_ids.push(f_client_id);
}
