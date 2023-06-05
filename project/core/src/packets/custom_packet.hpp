#ifndef CUSTOM_PACKET_HPP
#define CUSTOM_PACKET_HPP

#include "packet.hpp"

namespace AkashiNetwork {
    class PacketCustom : public AOJsonPacket
    {
        PacketCustom(QString type, QJsonObject f_object);
        PacketInfo getPacketInfo() const override;
        QByteArray serialize() const override;
        void setType(QString type);

      private:
        QString type;
        QJsonObject content;
    };
} // namespace AkashiNetwork
#endif // CUSTOM_PACKET_HPP
