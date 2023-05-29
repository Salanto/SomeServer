#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QObject>
#include <memory>

namespace AkashiNetwork
{
class NetworkSocket;
} // namespace AkashiNetwork

namespace AkashiCore
{
namespace Private
{
struct ClientPrivate;
} // namespace Private

class Client : public QObject
{
  Q_OBJECT

public:
  Client(QObject *parent, AkashiNetwork::NetworkSocket *f_socket, int client_id = -1);
  ~Client();

  int getId();

signals:
  void clientDisconnected(int f_client_id);

private:
  std::unique_ptr<Private::ClientPrivate> d_ptr;
};
} // namespace AkashiCore

#endif // CLIENT_HPP
