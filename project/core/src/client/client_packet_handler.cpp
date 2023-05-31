#include "client_packet_handler.hpp"

#include "area/hub_manager.hpp"
#include "client/client.hpp"
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

        m_handler_map["HI"] = &ClientPacketHandler::handle_HI;
    }

    void ClientPacketHandler::registerMappers()
    {
        m_handler_map["HI"] = &ClientPacketHandler::handle_HI;
        m_handler_map["ID"] = &ClientPacketHandler::handle_ID;
    }

    void ClientPacketHandler::handshake()
    {
        AkashiNetwork::PacketCustom packet("decryptor", {"NOENCRYPT"});
        handler->sendPacket(&packet);
    }

    void ClientPacketHandler::handle_HI(AkashiNetwork::AOPacket *f_packet)
    {
        qDebug() << "Received HI packet";
        AkashiNetwork::PacketCustom packet("ID", {"Akashi", "0.0.1"});
        handler->sendPacket(&packet);
    }

    void ClientPacketHandler::handlePacket(AkashiNetwork::AOPacket *packet)
    {
        qInfo() << "Client" << client->getId() << "sent packet:" << packet->getContent();
        (this->*m_handler_map[packet->getPacketInfo().header])(packet);
        delete packet;
    }
} // namespace AkashiCore
