#ifndef MASTERSERVER_CLIENT_HPP
#define MASTERSERVER_CLIENT_HPP

#include <QObject>
#include <memory>

class QNetworkReply;

namespace AkashiNetwork
{
namespace Private
{
struct MasterserverPrivate;
} // namespace Private

class MasterserverClient : public QObject
{
  Q_OBJECT

public:
  struct MS_ClientConfig
  {
    QString hostname;
    QString server_name;
    QString description;
    int playercount;
    int port;
    int ws_port;
    QString masterserver_hostname;
  };

  MasterserverClient(QObject *parent, MS_ClientConfig f_config);
  ~MasterserverClient();
  ;

public slots:
  void on_configReloadRequest(MS_ClientConfig f_config);
  void on_updatePlayercount(int f_player_count);
  void on_advertiseServerRequest();
  void on_masterserverReply(QNetworkReply *f_reply);

private:
  std::unique_ptr<Private::MasterserverPrivate> d_ptr;

  const int advertisingInterval = 5 * 1000 * 60;
};

} // namespace AkashiNetwork

#endif // MASTERSERVER_HPP
