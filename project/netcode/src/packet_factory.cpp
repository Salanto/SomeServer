#include "packet_factory.hpp"

#include <QDebug>

using namespace AkashiNetwork;

namespace AkashiNetwork
{
std::map<QString, AOPacket *(*)(QStringList)> PacketFactory::m_builder_map;

bool PacketFactory::canCreatePacket(QString header)
{
  return m_builder_map.count(header);
}

AOPacket *PacketFactory::createPacket(QString header, QStringList content)
{
  return m_builder_map[header](content);
}

void PacketFactory::registerPacket(AOPacket *(*builder)(QStringList))
{
  AOPacket *packet = (*builder)(QStringList{});
  PacketInfo info = packet->getPacketInfo();
  Q_ASSERT(!m_builder_map.count(info.header));
  m_builder_map[info.header] = builder;
  delete packet;
}
} // namespace AkashiNetwork

/*
AOPacket *PacketFactory_DEPRECATED::createPacket(QString header, QStringList contents)
{
  if (!class_map.count(header))
  {
    return createInstance<PacketGeneric>(header, contents);
  }

  return class_map[header](contents);
}

AOPacket *PacketFactory_DEPRECATED::createPacket(QString raw_packet)
{
  QString header;
  QStringList contents;

  if (raw_packet.isEmpty())
  {
    qDebug() << "Empty packet received.";
    return PacketFactory_DEPRECATED::createPacket("Unknown", {"Unknown"});
  }

  if (raw_packet.at(0) == '#' || raw_packet.contains("%"))
  {
    qDebug() << "FantaCrypt or otherwise invalid packet received";
    return PacketFactory_DEPRECATED::createPacket("Unknown", {"Unknown"});
  }

  QStringList packet_contents = raw_packet.split("#");
  header = packet_contents[0];
  packet_contents.removeFirst(); // Remove header

  if (!packet_contents.isEmpty())
  {
    packet_contents.removeLast(); // Remove anything trailing after delimiter
  }
  contents = packet_contents;

  AOPacket *packet = PacketFactory_DEPRECATED::createPacket(header, contents);
  packet->unescapeContent();

  return packet;
}
*/
