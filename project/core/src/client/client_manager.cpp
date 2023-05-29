#include "client_manager.hpp"
#include "client/client.hpp"
#include "client/client_manager_p.hpp"
#include "configuration/config_manager.hpp"
#include "interfaces/network_socket_i.hpp"
#include "packets/decryptor_packet.hpp"

#include <QDebug>

using namespace AkashiCore;

ClientManager::ClientManager(QObject *parent)
    : QObject(parent)
    , d_ptr(std::make_unique<Private::ClientManagerPrivate>())
{
  qDebug() << "[ClientManager]::CTOR"
           << "Starting ClientManager";

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
    l_socket->writeData("KB#TOOMANYPLAYERS#%");
    l_socket->deleteLater();
    return;
  }

  auto l_client = new Client(this, l_socket, d_ptr->player_ids.pop());
  connect(l_client, &Client::clientDisconnected, this, &ClientManager::on_clientDisconnected);
  d_ptr.get()->clients.insert(0, l_client);

  // initiate handshake
  QStringList content{"NOENCRYPT"};
  AkashiNetwork::PacketDECRYPTOR decryptor(content);
  l_socket->writeData(decryptor.toUtf8());
}

void ClientManager::on_clientDisconnected(int f_client_id)
{
  d_ptr.get()->player_ids.push(f_client_id);
  d_ptr.get()->clients[f_client_id]->deleteLater();
  d_ptr.get()->clients[f_client_id] = nullptr;
}
