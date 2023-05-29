#include "masterserver_client.hpp"
#include "masterserver_client_p.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

using namespace AkashiNetwork;

MasterserverClient::MasterserverClient(QObject *parent, MS_ClientConfig f_config)
    : QObject(parent)
    , d_ptr(std::make_unique<Private::MasterserverPrivate>())
{
  qDebug() << "[MASTERSERVER]::CTOR"
           << "Starting Masterserver Client";
  d_ptr.get()->hostname = f_config.hostname;
  d_ptr.get()->server_name = f_config.server_name;
  d_ptr.get()->description = f_config.description;
  d_ptr.get()->port = f_config.port;
  d_ptr.get()->ws_port = f_config.ws_port;
  if (!f_config.masterserver_hostname.isEmpty())
  {
    d_ptr.get()->masterserver_hostname = f_config.masterserver_hostname;
  }
  d_ptr.get()->playercount = f_config.playercount;

  connect(&d_ptr.get()->network, &QNetworkAccessManager::finished, this, &MasterserverClient::on_masterserverReply);
  connect(&d_ptr.get()->timer, &QTimer::timeout, this, &MasterserverClient::on_advertiseServerRequest);
  d_ptr.get()->timer.setTimerType(Qt::TimerType::CoarseTimer);
  d_ptr.get()->timer.setInterval(advertisingInterval);
  d_ptr.get()->timer.start();
  on_advertiseServerRequest();
}

MasterserverClient::~MasterserverClient()
{
  qDebug() << "[MASTERSERVER]::DTOR"
           << "Destroying Masterserver Client";
}

void MasterserverClient::on_configReloadRequest(MS_ClientConfig f_config)
{
  d_ptr.get()->hostname = f_config.hostname;
  d_ptr.get()->server_name = f_config.server_name;
  d_ptr.get()->description = f_config.description;
  d_ptr.get()->port = f_config.port;
  d_ptr.get()->ws_port = f_config.ws_port;
  if (!f_config.masterserver_hostname.isEmpty())
  {
    d_ptr.get()->masterserver_hostname = f_config.masterserver_hostname;
  }
  d_ptr.get()->playercount = f_config.playercount;
}

void MasterserverClient::on_updatePlayercount(int f_player_count)
{
  d_ptr.get()->playercount = f_player_count;
}

void MasterserverClient::on_advertiseServerRequest()
{
  QUrl url(d_ptr.get()->masterserver_hostname);
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  QJsonObject l_json;

  if (!d_ptr.get()->hostname.isEmpty())
  {
    l_json["ip"] = d_ptr.get()->hostname;
  }

  l_json["port"] = d_ptr.get()->port;
  if (d_ptr.get()->ws_port != -1)
  {
    l_json["ws_port"] = d_ptr.get()->ws_port;
  }

  l_json["players"] = d_ptr.get()->playercount;
  l_json["name"] = d_ptr.get()->server_name;

  if (!d_ptr.get()->description.isEmpty())
  {
    l_json["description"] = d_ptr.get()->description;
  }

  d_ptr.get()->network.post(request, QJsonDocument(l_json).toJson());
}

void MasterserverClient::on_masterserverReply(QNetworkReply *f_reply)
{
  if (f_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
  {
    qDebug().noquote() << "[MASTERSERVER]::AdvertiseReply"
                       << "Advertised server.";
  }
  else
  {
    QJsonDocument json = QJsonDocument::fromJson(f_reply->readAll());
    if (json.isNull())
    {
      qCritical().noquote() << "[MASTERVER]::AdvertiseError"
                            << "Invalid response from" << f_reply->url();
      f_reply->deleteLater();
      return;
    }

    qDebug().noquote() << "[MASTERSERVER]::AdvertiseError"
                       << "Response from" << f_reply->url();
    qDebug() << json;
  }
  f_reply->deleteLater();
}
