#include "id_packet.hpp"
#include <QDebug>

using namespace AkashiNetwork;

PacketID::PacketID(QStringList &contents)
    : AOPacket(contents)
{}

PacketInfo PacketID::getPacketInfo() const
{
  return PacketInfo{"ID", 2};
}

bool PacketID::validatePacket() const
{
  return true;
}
