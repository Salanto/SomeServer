#ifndef CUSTOM_PACKET_HPP
#define CUSTOM_PACKET_HPP

#include "packet.hpp"

namespace AkashiNetwork
{
class PacketCustom : public AOPacket
{
public:
  PacketCustom(QString header, QStringList contents);
  PacketInfo getPacketInfo() const override;
  bool validatePacket() const override;
  void setHeader(QString f_header);

private:
  QString header;
};
} // namespace AkashiNetwork
#endif // CUSTOM_PACKET_HPP
