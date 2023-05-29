#ifndef CLIENT_MANAGER_PRIVATE_HPP
#define CLIENT_MANAGER_PRIVATE_HPP

#include <QMap>
#include <QStack>

namespace AkashiArea
{
class HubManager;
} // namespace AkashiArea

namespace AkashiCore
{
class Client;
class ClientPacketHandler;

namespace Private
{
struct ClientManagerPrivate
{
  QStack<int> player_ids;
  QMap<int, AkashiCore::Client *> clients;
  QMap<int, AkashiCore::ClientPacketHandler *> client_handlers;
  AkashiArea::HubManager *hub_manager;
};
} // namespace Private
} // namespace AkashiCore
#endif // CLIENT_MANAGER_PRIVATE_HPP
