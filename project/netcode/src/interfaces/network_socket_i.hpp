#ifndef NETWORK_SOCKET_INTERFACE_HPP
#define NETWORK_SOCKET_INTERFACE_HPP

#include <QHostAddress>
#include <QObject>

namespace AkashiNetwork
{
class NetworkSocket : public QObject
{
  Q_OBJECT

public:
  NetworkSocket(QObject *parent)
      : QObject(parent){};
  ~NetworkSocket(){};

  virtual QHostAddress remoteIP() = 0;

  virtual QString pendingData() = 0;

protected:
  QHostAddress ip;

public slots:
  virtual void writeData(QByteArray f_data) = 0;

signals:
  void dataReceived();
  void dataReceivedByClient(int f_client_id, QString f_message_data);
  void disconnected();
};
} // namespace AkashiNetwork

#endif // NETWORK_SOCKET_INTERFACE_HPP
