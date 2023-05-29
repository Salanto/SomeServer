#include "client/client.hpp"
#include "client/client_p.hpp"
#include "interfaces/network_socket_i.hpp"

#include <QDebug>

AkashiCore::Client::Client(QObject *parent, AkashiNetwork::NetworkSocket *f_socket, int client_id)
    : QObject(parent)
    , d_ptr(std::make_unique<Private::ClientPrivate>())
{
  qDebug() << "[CLIENT]::CTOR"
           << "Creating client with id" << client_id;
  d_ptr.get()->id = client_id;
  d_ptr.get()->socket = f_socket;
  connect(d_ptr.get()->socket, &AkashiNetwork::NetworkSocket::disconnected, this, [=] { emit clientDisconnected(d_ptr.get()->id); });
}

AkashiCore::Client::~Client()
{
  qDebug() << "[CLIENT]::DTOR"
           << "Destroying Client with id" << d_ptr->id;
  d_ptr->socket->deleteLater();
}

int AkashiCore::Client::getId()
{
  return d_ptr.get()->id;
}
