#include "custom_packet.hpp"

namespace AkashiNetwork
{
PacketCustom::PacketCustom(QString header, QStringList content)
    : AOPacket(content)
{
  setHeader(header);
}

PacketInfo PacketCustom::getPacketInfo() const
{
  return PacketInfo{header, -1};
}

bool PacketCustom::validatePacket() const
{
  return true;
}

void PacketCustom::setHeader(QString f_header)
{
  header = f_header;
}
} // namespace AkashiNetwork
