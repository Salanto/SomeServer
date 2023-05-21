#ifndef HI_PACKET_HPP
#define HI_PACKET_HPP

#include "aoprotocol/include/packet.hpp"

namespace AkashiNetwork {
    class PacketHI : public AOPacket
    {
      public:
        PacketHI(QStringList &contents);
        virtual PacketInfo getPacketInfo() const;
        virtual bool validatePacket() const;

      private:
        QString header;
    };
}
#endif
