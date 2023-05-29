#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <QObject>
#include <memory>

namespace AkashiArea
{
class HubManager;
} // namespace AkashiArea

namespace AkashiNetwork
{
class NetworkSocket;
} // namespace AkashiNetwork

namespace AkashiCore
{
namespace Private
{
struct ClientManagerPrivate;
} // namespace Private

class ClientManager : public QObject
{
  Q_OBJECT

public:
  ClientManager(AkashiArea::HubManager *hub_manager, QObject *parent);
  ~ClientManager();

public slots:
  void on_newClientConnected(AkashiNetwork::NetworkSocket *l_socket);
  void on_clientDisconnected(int f_client_id);

private:
  std::unique_ptr<Private::ClientManagerPrivate> d_ptr;
};
} // namespace AkashiCore

#endif
