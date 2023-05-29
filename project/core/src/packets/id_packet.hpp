#ifndef ID_PACKET_HPP
#define ID_PACKET_HPP

#include "packet.hpp"

namespace AkashiNetwork
{
class PacketID : public AOPacket
{
public:
  PacketID(QStringList &contents);
  virtual PacketInfo getPacketInfo() const;
  virtual bool validatePacket() const;
};
} // namespace AkashiNetwork
#endif // ID_PACKET_HPP
