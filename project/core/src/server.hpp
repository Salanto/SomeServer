#ifndef SERVER_HPP
#define SERVER_HPP

#include <QCoreApplication>
#include <memory>

namespace AkashiArea
{
class HubManager;
} // namespace AkashiArea

namespace AkashiNetwork
{
class ConnectionHandler;
class MasterserverClient;
} // namespace AkashiNetwork

namespace AkashiCore
{
class ClientManager;

class Server : public QCoreApplication
{
  Q_OBJECT

public:
  Server(int argc, char *argv[]);
  ~Server();

private:
  AkashiNetwork::ConnectionHandler *connection_handler;
  AkashiNetwork::MasterserverClient *masterserver_client;
  AkashiArea::HubManager *hub_manager;
  AkashiCore::ClientManager *client_manager;
};
} // namespace AkashiCore

#endif // SERVER_HPP
