#ifndef JOIN_PACKET_HPP
#define JOIN_PACKET_HPP

#include "packet.hpp"

namespace AkashiNetwork {

    struct AOVersion
    {
        int major = 0;
        int minor = 0;
        int revision = 0;
    };

    struct JoinPacketContent
    {
        QString HWID;
        QString AppID;
        AOVersion version;
    };

    class JoinPacket : public AOJsonPacket
    {
      public:
        JoinPacket(QJsonObject f_object);
        ~JoinPacket(){};

        QByteArray serialize() const override;
        PacketInfo getPacketInfo() const override;
        JoinPacketContent getContent() const;

      private:
        JoinPacketContent f_content;
    };
}

#endif // JOIN_PACKET_HPP
