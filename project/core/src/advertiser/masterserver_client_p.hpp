#ifndef MASTERSERVER_CLIENT_PRIVATE_HPP
#define MASTERSERVER_CLIENT_PRIVATE_HPP

#include <QNetworkAccessManager>
#include <QString>
#include <QTimer>

namespace AkashiNetwork::Private
{
struct MasterserverPrivate
{
  QNetworkAccessManager network;
  QTimer timer;
  QString hostname;
  QString server_name;
  QString description;
  int playercount;
  int port;
  int ws_port;

  QString masterserver_hostname = "https://servers.aceattorneyonline.com/servers";
};
} // namespace AkashiNetwork::Private

#endif // MASTERSERVER_PRIVATE_HPP
