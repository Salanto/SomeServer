#ifndef AOWEBSOCKET_HPP
#define AOWEBSOCKET_HPP

#include "interfaces/network_socket_i.hpp"

class QWebSocket;

namespace AkashiNetwork
{
class AOWebSocket : public NetworkSocket
{
  Q_OBJECT

public:
  AOWebSocket(QObject *parent, QWebSocket *f_socket);
  ~AOWebSocket();

  QHostAddress remoteIP() override;

  QString pendingData() override;

public slots:
  void writeData(const QByteArray f_data) override;

private:
  QWebSocket *m_socket;
  QString m_buffer;

private slots:
  void receiveData(QString f_data = "");

  // NetworkSocket interface
public:
};
} // namespace AkashiNetwork
#endif // AOWEBSOCKET_HPP
