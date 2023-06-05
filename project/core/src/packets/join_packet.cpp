#include "join_packet.hpp"

using namespace AkashiNetwork;

JoinPacket::JoinPacket(QJsonObject f_object)
{
    f_content.HWID = f_object.value("HWID").toString();
    f_content.AppID = f_object.value("APPID").toString();

    QStringList l_version_split = f_object.value("VERSION").toString().split(".");
    if (l_version_split.size() > 2) {
        f_content.version.revision = l_version_split.at(2).toInt();
    }

    if (l_version_split.size() > 1) {
        f_content.version.minor = l_version_split.at(1).toInt();
    }

    if (l_version_split.size() > 0) {
        f_content.version.major = l_version_split.at(0).toInt();
    }
}

QByteArray JoinPacket::serialize() const
{
    qDebug("Unable to serialze client-only packet");
    return QByteArray();
}

PacketInfo JoinPacket::getPacketInfo() const
{
    return PacketInfo{"join", 3};
}
