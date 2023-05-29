#ifndef CONNECTION_HANDLER_HPP
#define CONNECTION_HANDLER_HPP

#include "interfaces/network_socket_i.hpp"

#include <QObject>
#include <memory>

namespace AkashiNetwork
{
namespace Private
{
struct ConnectionHandlerPrivate;
}; // namespace Private

class NetworkSocket;

// Accepts and rejects incoming connections and handles their disconnect gracefully.
class ConnectionHandler : public QObject
{
  Q_OBJECT

public:
  ConnectionHandler(QObject *parent, int port, int ws_port);
  ~ConnectionHandler();

signals:
  void newClientConnected(NetworkSocket *f_socket);

private:
  std::unique_ptr<Private::ConnectionHandlerPrivate> d_ptr;

  QVector<NetworkSocket *> m_sockets;

private slots:
  void handleTcpConnection();
  void handleWebConnection();
};

}; // namespace AkashiNetwork

#endif // CONNECITON_HANDLER_HPP
