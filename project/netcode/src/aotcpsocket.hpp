#ifndef AOTCPSOCKET_HPP
#define AOTCPSOCKET_HPP

#include "interfaces/network_socket_i.hpp"

class QTcpSocket;

namespace AkashiNetwork
{
class AOTCPSocket : public NetworkSocket
{
  Q_OBJECT

public:
  AOTCPSocket(QObject *parent, QTcpSocket *f_socket);
  ~AOTCPSocket();

  QHostAddress remoteIP() override;

  QString pendingData() override;

public slots:
  void writeData(const QByteArray f_data) override;

private:
  QTcpSocket *m_socket;
  QString m_buffer;

private slots:
  void receiveData();

  // NetworkSocket interface
public:
};
} // namespace AkashiNetwork
#endif // AOTCPSOCKET_HPP
