#ifndef CONNECTION_HANDLER_PRIVATE_HPP
#define CONNECTION_HANDLER_PRIVATE_HPP

#include <memory>

class QTcpServer;
class QWebSocketServer;

namespace AkashiNetwork::Private
{

struct ConnectionHandlerPrivate
{
  QTcpServer *tcp_server;
  QWebSocketServer *ws_server;
};
} // namespace AkashiNetwork::Private

#endif // CONNECTION_HANDLER_PRIVATE_HPP
