#ifndef PACKET_HPP
#define PACKET_HPP

#include "packet_info.hpp"
#include <QJsonObject>

namespace AkashiNetwork {
    class AOJsonPacket
    {
      public:
        AOJsonPacket();
        virtual ~AOJsonPacket();

        virtual QByteArray serialize() const = 0;
        virtual PacketInfo getPacketInfo() const = 0;
    };
} // namespace AkashiNetwork

#endif // PACKET_HPP
