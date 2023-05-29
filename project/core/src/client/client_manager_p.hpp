#ifndef CLIENT_MANAGER_PRIVATE_HPP
#define CLIENT_MANAGER_PRIVATE_HPP

#include <QStack>
#include <QVector>

namespace AkashiCore
{

class Client;

namespace Private
{
struct ClientManagerPrivate
{
  QVector<AkashiCore::Client *> clients;
  QStack<int> player_ids;
};
} // namespace Private
} // namespace AkashiCore

#endif
