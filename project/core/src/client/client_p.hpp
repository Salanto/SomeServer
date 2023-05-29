#ifndef CLIENT_PRIVATE_HPP
#define CLIENT_PRIVATE_HPP

namespace AkashiNetwork
{
class NetworkSocket;
} // namespace AkashiNetwork

namespace AkashiCore::Private
{
struct ClientPrivate
{
  AkashiNetwork::NetworkSocket *socket;
  int id;
};
} // namespace AkashiCore::Private

#endif
