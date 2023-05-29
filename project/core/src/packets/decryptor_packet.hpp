#ifndef DECRYPTOR_PACKET_HPP
#define DECRYPTOR_PACKET_HPP

#include "packet.hpp"

namespace AkashiNetwork
{
class PacketDECRYPTOR : public AOPacket
{
public:
  PacketDECRYPTOR(QStringList &contents);
  PacketInfo getPacketInfo() const override;
  bool validatePacket() const override;
};
} // namespace AkashiNetwork
#endif // DECRYPTOR_PACKET_HPP
