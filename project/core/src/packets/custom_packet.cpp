#include "custom_packet.hpp"

#include <QJsonDocument>

namespace AkashiNetwork {
    PacketCustom::PacketCustom(QString f_type, QJsonObject f_content) :
        AOJsonPacket(),
        content(f_content)
    {
        setType(f_type);
    }

    PacketInfo PacketCustom::getPacketInfo() const
    {
        return PacketInfo{type, -1};
    }

    QByteArray PacketCustom::serialize() const
    {
        QJsonObject f_content;
        f_content.insert("type", type);
        f_content.insert("content", content);

        QJsonDocument l_json(f_content);
        return l_json.toJson();
    }

    void PacketCustom::setType(QString f_type)
    {
        type = f_type;
    }
} // namespace AkashiNetwork
