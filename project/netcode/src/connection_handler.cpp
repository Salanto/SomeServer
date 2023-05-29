#include "connection_handler.hpp"
#include "aotcpsocket.hpp"
#include "aowebsocket.hpp"
#include "connection_handler_p.hpp"

#include <QDebug>
#include <QHostAddress>
#include <QTcpServer>
#include <QWebSocketServer>

using namespace AkashiNetwork;

ConnectionHandler::ConnectionHandler(QObject *parent, int port, int ws_port)
    : QObject(parent)
    , d_ptr(std::make_unique<Private::ConnectionHandlerPrivate>())
{
  qDebug() << "[ConnectionHandler]::CTOR"
           << "Starting ConnectionHandler";

  if (port != 0)
  {
    d_ptr->tcp_server = new QTcpServer(this);

    if (d_ptr->tcp_server->listen(QHostAddress::LocalHost, port))
    {
      qDebug() << "[ConnectionHandler]::CTOR"
               << "Listening for incoming TCP connection on port" << port;
      connect(d_ptr->tcp_server, &QTcpServer::newConnection, this, &ConnectionHandler::handleTcpConnection);
    }
    else
    {
      qDebug() << "[ConnectionHandler]::CTOR"
               << "An error occured starting the TCP Server:" << d_ptr->tcp_server->serverError();
    }
  }

  if (ws_port != 0)
  {
    d_ptr->ws_server = new QWebSocketServer("akashi", QWebSocketServer::SslMode::NonSecureMode, this);

    if (d_ptr->ws_server->listen(QHostAddress::LocalHost, ws_port))
    {
      qDebug() << "[ConnectionHandler]::CTOR"
               << "Listening for incoming Websocket connection on port" << ws_port;
      connect(d_ptr->ws_server, &QWebSocketServer::newConnection, this, &ConnectionHandler::handleWebConnection);
    }
    else
    {
      qDebug() << "[ConnectionHandler]::CTOR"
               << "An error occured starting the Websocket Server:" << d_ptr->tcp_server->serverError();
    }
  }
}

AkashiNetwork::ConnectionHandler::~ConnectionHandler()
{
  qDebug() << "[ConnectionHandler]::DTOR"
           << "Destroying ConnectionHandler";
}

void AkashiNetwork::ConnectionHandler::handleTcpConnection()
{
  qDebug() << "[ConnectionHandler]::TCPConnect"
           << "Incoming TCP connection.";
  QTcpSocket *l_new_socket = d_ptr->tcp_server->nextPendingConnection();

  AkashiNetwork::NetworkSocket *l_socket = new AkashiNetwork::AOTCPSocket(this, l_new_socket);
  emit newClientConnected(l_socket);
}

void AkashiNetwork::ConnectionHandler::handleWebConnection()
{
  qDebug() << "[ConnectionHandler]::WebSocketConnect"
           << "Incoming Websocket connection.";
  QWebSocket *l_new_socket = d_ptr->ws_server->nextPendingConnection();

  AkashiNetwork::NetworkSocket *l_socket = new AkashiNetwork::AOWebSocket(this, l_new_socket);
  emit newClientConnected(l_socket);
}
