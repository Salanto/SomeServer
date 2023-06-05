#include "client_packet_handler.hpp"

#include "area/hub_manager.hpp"
#include "client/client.hpp"
#include "configuration/config_manager.hpp"
#include "packet_handler.hpp"
#include "packets/custom_packet.hpp"

namespace AkashiCore {
    ClientPacketHandler::ClientPacketHandler(Client *client, AkashiNetwork::NetworkSocket *socket, AkashiArea::HubManager *hub_manager, QObject *parent) :
        QObject(parent),
        client(client),
        socket(socket),
        hub_manager(hub_manager),
        handler(new AkashiNetwork::PacketHandler(socket, this))
    {
        connect(handler, &AkashiNetwork::PacketHandler::packetReceived, this, &ClientPacketHandler::handlePacket);

        m_handler_map["join"] = &ClientPacketHandler::handle_join;
    }

    void ClientPacketHandler::registerMappers()
    {
        m_handler_map["join"] = &ClientPacketHandler::handle_join;
    }

    void ClientPacketHandler::handle_join(AkashiNetwork::AOJsonPacket *f_packet)
    {
        qDebug() << "Received join packet";
    }

    void ClientPacketHandler::handlePacket(AkashiNetwork::AOJsonPacket *packet)
    {
        qInfo() << "Client" << client->getId() << "sent packet:" << packet->getPacketInfo().header;
        (this->*m_handler_map[packet->getPacketInfo().header])(packet);
        delete packet;
    }
} // namespace AkashiCore
