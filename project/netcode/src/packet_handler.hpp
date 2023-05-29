#pragma once

#include "interfaces/network_socket_i.hpp"
#include "packet.hpp"

#include <QObject>

namespace AkashiNetwork
{
class PacketHandler : public QObject
{
  Q_OBJECT

public:
  explicit PacketHandler(NetworkSocket *socket, QObject *parent = nullptr);

  void sendPacket(AOPacket *packet);

signals:
  void packetReceived(AOPacket *packet);

private:
  NetworkSocket *m_socket;
  QString m_buffer;

private slots:
  void handleSocketData();
};
} // namespace AkashiNetwork
