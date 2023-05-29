#include "decryptor_packet.hpp"

namespace AkashiNetwork
{
PacketDECRYPTOR::PacketDECRYPTOR(QStringList &contents)
    : AOPacket(contents)
{}

PacketInfo PacketDECRYPTOR::getPacketInfo() const
{
  return PacketInfo{"decryptor", 1};
}

bool PacketDECRYPTOR::validatePacket() const
{
  return true;
}
} // namespace AkashiNetwork
