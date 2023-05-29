#ifndef CLIENT_PACKET_HANDLER_HPP
#define CLIENT_PACKET_HANDLER_HPP

#include "interfaces/network_socket_i.hpp"

#include <QObject>

namespace AkashiArea
{
class HubManager;
} // namespace AkashiArea

namespace AkashiNetwork
{
class AOPacket;
class PacketHandler;
} // namespace AkashiNetwork

namespace AkashiCore
{
class Client;

class ClientPacketHandler : public QObject
{
  Q_OBJECT

public:
  ClientPacketHandler(Client *client, AkashiNetwork::NetworkSocket *socket, AkashiArea::HubManager *hub_manager, QObject *parent = nullptr);

  void handshake();

signals:

private:
  Client *client;
  AkashiNetwork::NetworkSocket *socket;
  AkashiArea::HubManager *hub_manager;
  AkashiNetwork::PacketHandler *handler;

private slots:
  void handlePacket(AkashiNetwork::AOPacket *packet);
};
} // namespace AkashiCore
#endif // CLIENT_PACKET_HANDLER_HPP
