#include "packet_handler.hpp"

#include "packet_factory.hpp"

namespace AkashiNetwork
{
PacketHandler::PacketHandler(NetworkSocket *socket, QObject *parent)
    : QObject(parent)
    , m_socket(socket)
{
  connect(socket, &NetworkSocket::dataReceived, this, &PacketHandler::handleSocketData);
}

void PacketHandler::sendPacket(AOPacket *packet)
{
  m_socket->writeData(packet->toUtf8());
}

void PacketHandler::handleSocketData()
{
  m_buffer += m_socket->pendingData();
  if (!m_buffer.contains("#%"))
  {
    return;
  }

  QStringList split_buffer = m_buffer.split("%", Qt::KeepEmptyParts);
  m_buffer = split_buffer.takeLast();
  for (const QString &i_buffer : split_buffer)
  {
    QStringList content = i_buffer.split("#", Qt::KeepEmptyParts);
    content.takeLast();

    QString header = content.takeFirst();
    if (!PacketFactory::canCreatePacket(header))
    {
      qWarning() << "Unknown packet received:" << i_buffer;
      continue;
    }
    AOPacket *packet = PacketFactory::createPacket(header, content);
    emit packetReceived(packet);
  }
}
} // namespace AkashiNetwork
