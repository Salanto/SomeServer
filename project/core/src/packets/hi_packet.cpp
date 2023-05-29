#include "hi_packet.hpp"

#include <QDebug>

using namespace AkashiNetwork;

PacketHI::PacketHI(QStringList &contents)
    : AOPacket(contents)
{}

PacketInfo PacketHI::getPacketInfo() const
{
  return PacketInfo{"HI", 1};
}

bool PacketHI::validatePacket() const
{
  // We can always convert a string to a string. No point in checking.
  return true;
}
