#include "packet_factory.hpp"

#include <QDebug>

using namespace AkashiNetwork;

namespace AkashiNetwork {
    std::map<QString, AOJsonPacket *(*)(QJsonObject)> PacketFactory::m_builder_map;

    bool PacketFactory::canCreatePacket(QString header)
    {
        return m_builder_map.count(header);
    }

    AOJsonPacket *PacketFactory::createPacket(QString header, QJsonObject content)
    {
        return m_builder_map[header](content);
    }

    void PacketFactory::registerPacket(AOJsonPacket *(*builder)(QJsonObject))
    {
        AOJsonPacket *packet = (*builder)(QJsonObject{});
        PacketInfo info = packet->getPacketInfo();
        Q_ASSERT(!m_builder_map.count(info.header));
        m_builder_map[info.header] = builder;
        delete packet;
    }

} // namespace AkashiNetwork
